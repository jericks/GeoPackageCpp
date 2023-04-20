#include "Polygon.hpp"

namespace geopackage {

    Polygon::Polygon(LinearRing ring) : rings(std::vector<LinearRing> {ring}) {}

    Polygon::Polygon(std::vector<LinearRing> rngs) : rings(rngs) {}

    std::unique_ptr<Geometry> Polygon::clone() const  {
        auto polygon = std::make_unique<Polygon>(rings);
        polygon->setSrid(getSrid());
        return polygon;
    }

    GeometryType Polygon::getType() const {
        return GeometryType::POLYGON;
    }

    Dimension Polygon::getDimension() const {
        if (rings.size() == 0) {
            return Dimension::Two;
        } else {
            return rings[0].getDimension();
        }
    }

    std::string Polygon::wkt() const {
        return WKTWriter{}.write(this);
    }

    bool Polygon::isEmpty() const {
        return rings.empty();
    }

    std::vector<LinearRing> Polygon::getLinearRings() const {
        return rings;
    }

}