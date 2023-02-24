#include "WKBWriter.hpp"

namespace geopackage {
    
    WKBWriter::WKBWriter() : type(wkb::Type::WKB), endian(Endian::BIG) {}

    WKBWriter::WKBWriter(wkb::Type type, Endian endian) : type(type), endian(endian) {}

    Bytes WKBWriter::writeToBytes(Geometry* geometry) {
        Bytes bytes {endian};
        putByteOrder(endian, bytes);
        putGeometryType(geometry->getType(), geometry->getDimension(), geometry->getSrid(), bytes);
        putSrid(geometry->getSrid(), bytes);
        putGeometry(geometry, bytes);
        return bytes;
    }

    std::vector<std::byte> WKBWriter::write(Geometry* geometry) {
        return writeToBytes(geometry).getBytes();
    }

    std::string WKBWriter::writeToHex(Geometry* geometry) {
        return writeToBytes(geometry).toHexString();
    }

    void WKBWriter::putByteOrder(Endian byteOrder, Bytes& bytes) {
        std::byte endianByte = endian == Endian::BIG ? std::byte{0} : std::byte{1};
        bytes.putByte(endianByte);
    }

    void WKBWriter::putGeometryType(GeometryType geometryType, Dimension dimension, std::string srid, Bytes& bytes) {
        int geometryTypeValue = geometrytype::getValue(geometryType);
        if (type == wkb::Type::EWKB) {
            if (dimension == Dimension::Three || dimension == Dimension::ThreeMeasured) {
                geometryTypeValue = geometryTypeValue | 0x80000000;
            }
            if (dimension == Dimension::TwoMeasured || dimension == Dimension::ThreeMeasured) {
                geometryTypeValue = geometryTypeValue | 0x40000000;
            } 
            if (!srid.empty()) {
                geometryTypeValue = geometryTypeValue | 0x20000000;
            }
        }
        bytes.putInt(geometryTypeValue);
    }

    void WKBWriter::putSrid(std::string srid, Bytes& bytes) {
        if (type == wkb::Type::EWKB && !srid.empty()) {
            bytes.putInt(std::stoi(srid));
        }
    }

    void WKBWriter::putGeometry(Geometry* geometry, Bytes& bytes) {
        GeometryType geometryType = geometry->getType();
        if (geometryType == GeometryType::POINT) {
            Point* pt = static_cast<Point *>(geometry);
            putPoint(pt, bytes);
        } else  if (geometryType == GeometryType::LINESTRING) {
            LineString* line = static_cast<LineString *>(geometry);
            putLineString(line, bytes);
        } else  if (geometryType == GeometryType::POLYGON) {
            Polygon* polygon = static_cast<Polygon *>(geometry);
            putPolygon(polygon, bytes);
        } else if (geometryType == GeometryType::MULTIPOINT) {
            MultiPoint* multiPoint = static_cast<MultiPoint *>(geometry);
            putMultiPoint(multiPoint, bytes);
        } else  if (geometryType == GeometryType::MULTILINESTRING) {
            MultiLineString* multiLineString = static_cast<MultiLineString *>(geometry);
            putMultiLineString(multiLineString, bytes);
        } else  if (geometryType == GeometryType::MULTIPOLYGON) {
            MultiPolygon* multiPolygon = static_cast<MultiPolygon *>(geometry);
            putMultiPolygon(multiPolygon, bytes);
        } else  if (geometryType == GeometryType::GEOMETRYCOLLECTION) {
            GeometryCollection* gc = static_cast<GeometryCollection *>(geometry);
            putGeometryCollection(gc, bytes);
        }
    }

    void WKBWriter::putPoint(const Point* point, Bytes& bytes) {
        bytes.putDouble(point->getX());
        bytes.putDouble(point->getY());
        Dimension dimension = point->getDimension();
        if (dimension == Dimension::Three || dimension == Dimension::ThreeMeasured) {
            bytes.putDouble(point->getZ());
        }
        if (dimension == Dimension::TwoMeasured || dimension == Dimension::ThreeMeasured) {
            bytes.putDouble(point->getM());
        }
    }

    void WKBWriter::putPoints(const std::vector<Point> points, Bytes& bytes) {
        bytes.putInt(points.size());
        for(const Point& point : points) {
            putPoint(&point, bytes);
        }
    }

    void WKBWriter::putLineString(const LineString* line, Bytes& bytes) {
        putPoints(line->getPoints(), bytes);
    }

    void WKBWriter::putPolygon(const Polygon* polygon, Bytes& bytes) {
        bytes.putInt(polygon->getLinearRings().size());
        for(const LinearRing& ring : polygon->getLinearRings()) {
            putPoints(ring.getPoints(), bytes);
        }
    }

    void WKBWriter::putMultiPoint(const MultiPoint* multiPoint, Bytes& bytes) {
        bytes.putInt(multiPoint->getPoints().size());
        for(const Point& point : multiPoint->getPoints()) {
            putByteOrder(endian, bytes);
            putGeometryType(point.getType(), point.getDimension(), point.getSrid(), bytes);
            putSrid(point.getSrid(), bytes);
            putPoint(&point, bytes);
        }
    }

    void WKBWriter::putMultiLineString(const MultiLineString* multiLineString, Bytes& bytes) {
        bytes.putInt(multiLineString->getLineStrings().size());
        for(const LineString& lineString : multiLineString->getLineStrings()) {
            putByteOrder(endian, bytes);
            putGeometryType(lineString.getType(), lineString.getDimension(), lineString.getSrid(), bytes);
            putSrid(lineString.getSrid(), bytes);
            putLineString(&lineString, bytes);
        }
    }

    void WKBWriter::putMultiPolygon(const MultiPolygon* multiPolygon, Bytes& bytes) {
        bytes.putInt(multiPolygon->getPolygons().size());
        for(const Polygon& polygon : multiPolygon->getPolygons()) {
            putByteOrder(endian, bytes);
            putGeometryType(polygon.getType(), polygon.getDimension(), polygon.getSrid(), bytes);
            putSrid(polygon.getSrid(), bytes);
            putPolygon(&polygon, bytes);
        }
    }

    void WKBWriter::putGeometryCollection(GeometryCollection* geometryCollection, Bytes& bytes) {
        int numberOfGeometries = geometryCollection->getNumberOfGeometries();
        bytes.putInt(numberOfGeometries);
        for(std::unique_ptr<Geometry>& geometry : geometryCollection->getGeometries()) {
            putByteOrder(endian, bytes);
            putGeometryType(geometry->getType(), geometry->getDimension(), geometry->getSrid(), bytes);
            putSrid(geometry->getSrid(), bytes);
            putGeometry(geometry.get(), bytes);
        }
    }

}