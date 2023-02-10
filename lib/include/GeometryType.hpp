#pragma once

#include <string>

namespace geopackage {

    enum class GeometryType {
        GEOMETRY, POINT, LINESTRING, POLYGON, MULTIPOINT, MULTILINESTRING, MULTIPOLYGON, GEOMETRYCOLLECTION
    };

    namespace geometrytype {

        std::string toString(GeometryType geometryType);

        GeometryType getGeometryType(std::string str);

    }

    std::ostream& operator << (std::ostream& os, const GeometryType& geometryType);

}