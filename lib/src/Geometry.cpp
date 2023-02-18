#include "Geometry.hpp"

namespace geopackage {

    std::ostream& operator << (std::ostream& os, const Geometry& geometry) {
        os << geometry.wkt();
        return os;
    }

}