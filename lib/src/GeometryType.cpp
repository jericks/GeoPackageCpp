#include "GeometryType.hpp"

namespace geopackage {

    namespace geometrytype {

        std::string toString(GeometryType geometryType) {
            if (geometryType == GeometryType::POINT) {
                return "point";
            } else if (geometryType == GeometryType::LINESTRING) {
                return "linestring";
            } else if (geometryType == GeometryType::LINEARRING) {
                return "linearring";
            } else if (geometryType == GeometryType::POLYGON) {
                return "polygon";
            } else if (geometryType == GeometryType::MULTIPOINT) {
                return "multipoint";
            } else if (geometryType == GeometryType::MULTILINESTRING) {
                return "multilinestring";
            } else if (geometryType == GeometryType::MULTIPOLYGON) {
                return "multipolygon";
            } else if (geometryType == GeometryType::GEOMETRYCOLLECTION) {
                return "geometrycollection";
            } else {
                return "geometry";
            }
        }

        GeometryType getGeometryType(std::string str) {
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