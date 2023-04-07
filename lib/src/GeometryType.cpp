#include "GeometryType.hpp"

namespace geopackage {

    namespace geometrytype {

        std::string toString(GeometryType geometryType) {
            if (geometryType == GeometryType::POINT) {
                return "Point";
            } else if (geometryType == GeometryType::LINESTRING) {
                return "LineString";
            } else if (geometryType == GeometryType::LINEARRING) {
                return "LinearRing";
            } else if (geometryType == GeometryType::POLYGON) {
                return "Polygon";
            } else if (geometryType == GeometryType::MULTIPOINT) {
                return "MultiPoint";
            } else if (geometryType == GeometryType::MULTILINESTRING) {
                return "MultiLineString";
            } else if (geometryType == GeometryType::MULTIPOLYGON) {
                return "MultiPolygon";
            } else if (geometryType == GeometryType::GEOMETRYCOLLECTION) {
                return "GeometryCollection";
            } else {
                return "Geometry";
            }
        }

        GeometryType getGeometryType(int value) {
            if (value == 1) {
                return GeometryType::POINT;
            } else if (value == 2) {
                return GeometryType::LINESTRING;
            } else if (value == 3) {
                return GeometryType::POLYGON;
            } else if (value == 4) {
                return GeometryType::MULTIPOINT;
            } else if (value == 5) {
                return GeometryType::MULTILINESTRING;
            } else if (value == 6) {
                return GeometryType::MULTIPOLYGON;
            } else if (value == 7) {
                return GeometryType::GEOMETRYCOLLECTION;
            } else {
                return GeometryType::GEOMETRY;
            }
        }

        GeometryType getGeometryType(std::string str) {
            std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c){ return std::tolower(c); });
            if (str == "point") {
                return GeometryType::POINT;
            } else if (str == "linestring") {
                return GeometryType::LINESTRING;
            } else if (str == "linearring") {
                return GeometryType::LINEARRING;
            } else if (str == "polygon") {
                return GeometryType::POLYGON;
            } else if (str == "multipoint") {
                return GeometryType::MULTIPOINT;
            } else if (str == "multilinestring") {
                return GeometryType::MULTILINESTRING;
            } else if (str == "multipolygon") {
                return GeometryType::MULTIPOLYGON;
            } else {
                return GeometryType::GEOMETRY;
            }
        }

        int getValue(GeometryType geometryType) {
            if (geometryType == GeometryType::POINT) {
                return 1;
            } else if (geometryType == GeometryType::LINESTRING) {
                return 2;
            } else if (geometryType == GeometryType::POLYGON) {
                return 3;
            } else if (geometryType == GeometryType::MULTIPOINT) {
                return 4;
            } else if (geometryType == GeometryType::MULTILINESTRING) {
                return 5;
            } else if (geometryType == GeometryType::MULTIPOLYGON) {
                return 6;
            } else if (geometryType == GeometryType::GEOMETRYCOLLECTION) {
                return 7;
            } else {
                return 0;
            }
        }

    }

    std::ostream& operator << (std::ostream& os, const GeometryType& geometryType) {
        os << geometrytype::toString(geometryType);
        return os;
    }

}