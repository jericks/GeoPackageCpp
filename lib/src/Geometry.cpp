#include "Geometry.hpp"

namespace geopackage {

    std::string Geometry::getSrid() const {
        return srid;
    }

    void Geometry::setSrid(const std::string s) {
        srid = s;
    }

    std::ostream& operator << (std::ostream& os, const Geometry& geometry) {
        os << geometry.wkt();
        return os;
    }

}