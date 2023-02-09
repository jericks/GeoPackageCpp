#include "GeometryType.hpp"

namespace geopackage {

    namespace geometrytype {

        std::string toString(GeometryType geometryType) {
            if (geometryType == GeometryType::POINT) {
                return "point";
            } else if (geometryType == GeometryType::LINESTRING) {
                return "linestring";
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

    }

}