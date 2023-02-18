#pragma once

#include <string>
#include <type_traits>

namespace geopackage {

    enum class GeometryType {
        GEOMETRY, POINT, LINESTRING, POLYGON, MULTIPOINT, MULTILINESTRING, MULTIPOLYGON, GEOMETRYCOLLECTION, LINEARRING
    };

    namespace geometrytype {

        std::string toString(GeometryType geometryType);

        GeometryType getGeometryType(std::string str);

        int getValue(GeometryType geometryType);

    }

    std::ostream& operator << (std::ostream& os, const GeometryType& geometryType);

}