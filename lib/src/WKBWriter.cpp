#include "WKBWriter.hpp"

namespace geopackage {
    
    std::vector<std::byte> WKBWriter::write(Geometry* geometry) {
        std::vector<std::byte> bytes {};
        putByteOrder(endian, bytes);
        putGeometryType(geometry->getType(), bytes);
        putGeometry(geometry, bytes);
        return bytes;
    }

    std::string WKBWriter::writeToHex(Geometry* geometry) {
         std::vector<std::byte> bytes = write(geometry);
        return toHexString(bytes);
    }

    void WKBWriter::putByteOrder(wkb::Endian byteOrder, std::vector<std::byte>& bytes) {
        std::byte endianByte = endian == wkb::Endian::BIG ? std::byte{0} : std::byte{1};
        bytes.push_back(endianByte);
    }

    void WKBWriter::putGeometryType(GeometryType geometryType, std::vector<std::byte>& bytes) {
        int geometryTypeValue = geometrytype::getValue(geometryType);
        putInt(geometryTypeValue, bytes);
    }

    void WKBWriter::putGeometry(Geometry* geometry, std::vector<std::byte>& bytes) {
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

    void WKBWriter::putPoint(const Point* point, std::vector<std::byte>& bytes) {
        putDouble(point->getX(), bytes);
        putDouble(point->getY(), bytes);
    }

    void WKBWriter::putPoints(const std::vector<Point> points, std::vector<std::byte>& bytes) {
        putInt(points.size(), bytes);
        for(const Point& point : points) {
            putPoint(&point, bytes);
        }
    }

    void WKBWriter::putLineString(const LineString* line, std::vector<std::byte>& bytes) {
        putPoints(line->getPoints(), bytes);
    }

    void WKBWriter::putPolygon(const Polygon* polygon, std::vector<std::byte>& bytes) {
        putInt(polygon->getLinearRings().size(), bytes);
        for(const LinearRing& ring : polygon->getLinearRings()) {
            putPoints(ring.getPoints(), bytes);
        }
    }

    void WKBWriter::putMultiPoint(const MultiPoint* multiPoint, std::vector<std::byte>& bytes) {
        putInt(multiPoint->getPoints().size(), bytes);
        for(const Point& point : multiPoint->getPoints()) {
            putByteOrder(endian, bytes);
            putGeometryType(point.getType(), bytes);
            putPoint(&point, bytes);
        }
    }

    void WKBWriter::putMultiLineString(const MultiLineString* multiLineString, std::vector<std::byte>& bytes) {
        putInt(multiLineString->getLineStrings().size(), bytes);
        for(const LineString& lineString : multiLineString->getLineStrings()) {
            putByteOrder(endian, bytes);
            putGeometryType(lineString.getType(), bytes);
            putLineString(&lineString, bytes);
        }
    }

    void WKBWriter::putMultiPolygon(const MultiPolygon* multiPolygon, std::vector<std::byte>& bytes) {
        putInt(multiPolygon->getPolygons().size(), bytes);
        for(const Polygon& polygon : multiPolygon->getPolygons()) {
            putByteOrder(endian, bytes);
            putGeometryType(polygon.getType(), bytes);
            putPolygon(&polygon, bytes);
        }
    }

    void WKBWriter::putGeometryCollection(GeometryCollection* geometryCollection, std::vector<std::byte>& bytes) {
        int numberOfGeometries = geometryCollection->getNumberOfGeometries();
        putInt(numberOfGeometries, bytes);
        for(std::unique_ptr<Geometry>& geometry : geometryCollection->getGeometries()) {
            putByteOrder(endian, bytes);
            putGeometryType(geometry->getType(), bytes);
            putGeometry(geometry.get(), bytes);
        }
    }

    void WKBWriter::putInt(int value, std::vector<std::byte>& bytes) {
        if(endian == wkb::Endian::BIG) {
            bytes.push_back(static_cast<std::byte>(value >> 24));
            bytes.push_back(static_cast<std::byte>(value >> 16));
            bytes.push_back(static_cast<std::byte>(value >> 8));
            bytes.push_back(static_cast<std::byte>(value));
        } else { 
            bytes.push_back(static_cast<std::byte>(value));
            bytes.push_back(static_cast<std::byte>(value >> 8));
            bytes.push_back(static_cast<std::byte>(value >> 16));
            bytes.push_back(static_cast<std::byte>(value >> 24));
        }
    }

    void WKBWriter::putLong(long value, std::vector<std::byte>& bytes) {
        if(endian == wkb::Endian::BIG) {
            bytes.push_back(static_cast<std::byte>(value >> 56));
            bytes.push_back(static_cast<std::byte>(value >> 48));
            bytes.push_back(static_cast<std::byte>(value >> 40));
            bytes.push_back(static_cast<std::byte>(value >> 32));
            bytes.push_back(static_cast<std::byte>(value >> 24));
            bytes.push_back(static_cast<std::byte>(value >> 16));
            bytes.push_back(static_cast<std::byte>(value >> 8));
            bytes.push_back(static_cast<std::byte>(value));
        } else { 
            bytes.push_back(static_cast<std::byte>(value));
            bytes.push_back(static_cast<std::byte>(value >> 8));
            bytes.push_back(static_cast<std::byte>(value >> 16));
            bytes.push_back(static_cast<std::byte>(value >> 24));
            bytes.push_back(static_cast<std::byte>(value >> 32));
            bytes.push_back(static_cast<std::byte>(value >> 40));
            bytes.push_back(static_cast<std::byte>(value >> 48));
            bytes.push_back(static_cast<std::byte>(value >> 56));
        }
    }

    void WKBWriter::putDouble(double value, std::vector<std::byte>& bytes) {
        int64_t longValue;
        std::memcpy(&longValue, &value, sizeof(double));
        putLong(longValue, bytes);
    }

    std::string WKBWriter::toHexString(std::vector<std::byte>& bytes) {
        std::stringstream ss;
        ss << std::hex << std::uppercase;
        for (int i = 0; i < bytes.size(); ++i) {
            ss << std::setw(2) << std::setfill('0') << (int)bytes[i];
        }
        return ss.str();
    }

}