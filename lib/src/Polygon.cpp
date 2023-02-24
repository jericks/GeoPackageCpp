#include "Polygon.hpp"

namespace geopackage {

    Polygon::Polygon(LinearRing ring) : rings(std::vector<LinearRing> {ring}) {}

    Polygon::Polygon(std::vector<LinearRing> rngs) : rings(rngs) {}

    std::unique_ptr<Geometry> Polygon::clone() const  {
        return std::make_unique<Polygon>(rings);
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
        std::stringstream str;
        str << "POLYGON ";
        if (std::size(rings) == 0) {
            str << "EMPTY";    
        } else {
            str << "(";
            bool firstLinearRing = true;
            for(auto r : rings) {
                if (firstLinearRing != true) {
                    str << ", ";
                }
                firstLinearRing = false;
                str << "(";
                bool firstTime = true;
                for(auto p : r.getPoints()) {
                    if (firstTime != true) {
                        str << ", ";
                    }
                    firstTime = false;
                    str << p.getX() << " " << p.getY();
                }
                str << ")";
            }
            str <<  ")";
        }
        return str.str();
    }

    bool Polygon::isEmpty() const {
        return rings.empty();
    }

    std::vector<LinearRing> Polygon::getLinearRings() const {
        return rings;
    }

}