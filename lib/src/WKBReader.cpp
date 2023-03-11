#include "WKBReader.hpp"

namespace geopackage {

    std::unique_ptr<Geometry> WKBReader::read(std::vector<std::byte> byteArray) {
        // Byte order
        std::byte byteOrderByte = byteArray[0];
        int byteOrderInt = std::to_integer<int>(byteOrderByte);
        Endian endian = byteOrderInt == 0 ? Endian::BIG : Endian::LITTLE;
        Bytes bytes {endian, byteArray};
        return read(bytes);
    }

    std::unique_ptr<Geometry> WKBReader::read(Bytes& bytes) {    

        // Byte order
        std::byte byteOrderByte = bytes.getByte();

        // Geometry Type
        int geometryTypeInt = bytes.getInt();

        // Dimension
        bool hasM = false;
        bool hasZ = false;
        bool hasSRID = false;

        int mFlag = 0x40000000;
        int zFlag = 0x80000000;
        int sridFlag = 0x20000000;

        // M
        if ((geometryTypeInt & mFlag) == mFlag) {
            hasM = true;
            geometryTypeInt = geometryTypeInt - mFlag;
        }

        // Z
        if ((geometryTypeInt & zFlag) == zFlag) {
            hasZ = true;
            geometryTypeInt = geometryTypeInt - zFlag;
        }
        
        // SRID
        if ((geometryTypeInt & sridFlag) == sridFlag) {
            hasSRID = true;
            geometryTypeInt = geometryTypeInt - sridFlag;
        }
        
        GeometryType geometryType = geometrytype::getGeometryType(geometryTypeInt);
        
        Dimension dimension;
        if (hasZ && hasM) {
            dimension = Dimension::ThreeMeasured;
        } else if (hasZ) {
            dimension = Dimension::Three;
        } else if (hasM) {
            dimension = Dimension::TwoMeasured;
        } else {
            dimension = Dimension::Two;
        }

        // SRID
        std::string srid = "";
        if (hasSRID) {
            int sridId = bytes.getInt();
            std::stringstream ss;
            ss << sridId;
            srid = ss.str();    
        }

        // Geometry
        return read(bytes, geometryType, dimension, srid);
    }

    std::unique_ptr<Geometry> WKBReader::read(Bytes& bytes, GeometryType geometryType, Dimension dimension, std::string srid) {
        if (geometryType == GeometryType::POINT) {
            Point point = getPoint(bytes, dimension);
            point.setSrid(srid);
            return std::make_unique<Point>(point);
        } else if (geometryType == GeometryType::LINESTRING) {
            LineString line = getLineString(bytes, dimension);
            line.setSrid(srid);
            return std::make_unique<LineString>(line);
        } else if (geometryType == GeometryType::POLYGON) {
            Polygon polygon = getPolygon(bytes, dimension);
            polygon.setSrid(srid);
            return std::make_unique<Polygon>(polygon);
        } else if (geometryType == GeometryType::MULTIPOINT) {
            MultiPoint multiPoint = getMultiPoint(bytes, dimension);
            multiPoint.setSrid(srid);
            return std::make_unique<MultiPoint>(multiPoint);
        } else if (geometryType == GeometryType::MULTILINESTRING) {
            MultiLineString multiLine = getMultiLineString(bytes, dimension);
            multiLine.setSrid(srid);
            return std::make_unique<MultiLineString>(multiLine);
        } else if (geometryType == GeometryType::MULTIPOLYGON) {
            MultiPolygon multiPolygon = getMultiPolygon(bytes, dimension);
            multiPolygon.setSrid(srid);
            return std::make_unique<MultiPolygon>(multiPolygon);
        } else if (geometryType == GeometryType::GEOMETRYCOLLECTION) {
            GeometryCollection geometryCollection = getGeometryCollection(bytes, dimension);
            geometryCollection.setSrid(srid);
            return geometryCollection.clone();
        } else {
            return nullptr;
        }
    }

    Point WKBReader::getPoint(Bytes& bytes, Dimension dimension) {
        double x = bytes.getDouble();
        double y = bytes.getDouble();
        double z = NAN;
        double m = NAN;
        if (dimension == Dimension::Three || dimension == Dimension::ThreeMeasured) {
            z = bytes.getDouble();
        }
        if (dimension == Dimension::ThreeMeasured || dimension == Dimension::TwoMeasured) {
            m = bytes.getDouble();
        }
        return Point{x,y,z,m};
    }

    LineString WKBReader::getLineString(Bytes& bytes, Dimension dimension) {
        int numberOfPoints = bytes.getInt();
        std::vector<Point> points;
        for(int i = 0; i < numberOfPoints; i++) {
            points.push_back(getPoint(bytes, dimension));
        }
        return LineString{points};
    }

    Polygon WKBReader::getPolygon(Bytes& bytes, Dimension dimension) {
        int numberOfRings = bytes.getInt();
        std::vector<LinearRing> points;
        for(int i = 0; i < numberOfRings; i++) {
            points.push_back(getLinearRing(bytes, dimension));
        }
        return Polygon{points};
    }

    LinearRing WKBReader::getLinearRing(Bytes& bytes, Dimension dimension) {
        int numberOfPoints = bytes.getInt();
        std::vector<Point> points;
        for(int i = 0; i < numberOfPoints; i++) {
            points.push_back(getPoint(bytes, dimension));
        }
        return LinearRing{points};
    }

    MultiPoint WKBReader::getMultiPoint(Bytes& bytes, Dimension dimension) {
        int numberOfPoints = bytes.getInt();
        std::vector<Point> points;
        for(int i = 0; i < numberOfPoints; i++) {
            std::unique_ptr<Geometry> geom = read(bytes);
            Point* pt = static_cast<Point *>(geom.get());
            points.push_back(Point{pt->getX(), pt->getY(), pt->getZ(), pt->getM()});
        }
        return MultiPoint{points};
    }

    MultiLineString WKBReader::getMultiLineString(Bytes& bytes, Dimension dimension) {
        int numberOfLines = bytes.getInt();
        std::vector<LineString> lines;
        for(int i = 0; i < numberOfLines; i++) {
            std::unique_ptr<Geometry> geom = read(bytes);
            LineString* line = static_cast<LineString *>(geom.get());
            lines.push_back(LineString{line->getPoints()});
        }
        return MultiLineString{lines};
    }

    MultiPolygon WKBReader::getMultiPolygon(Bytes& bytes, Dimension dimension)  {
        int numberOfPolygons = bytes.getInt();
        std::vector<Polygon> polygons;
        for(int i = 0; i < numberOfPolygons; i++) {
            std::unique_ptr<Geometry> geom = read(bytes);
            Polygon* polygon = static_cast<Polygon *>(geom.get());
            polygons.push_back(Polygon{polygon->getLinearRings()});
        }
        return MultiPolygon{polygons};
    }

    GeometryCollection WKBReader::getGeometryCollection(Bytes& bytes, Dimension dimension) {
        int numberOfGeometries = bytes.getInt();
        std::vector<std::unique_ptr<Geometry>> geometries;
        for(int i = 0; i < numberOfGeometries; i++) {
            std::unique_ptr<Geometry> geom = read(bytes);
            geometries.push_back(geom->clone());
        }
        GeometryCollection geometryCollection {std::move(geometries)};
        return geometryCollection;
    }

}