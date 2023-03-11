#include "MultiPolygon.hpp"

namespace geopackage {

    MultiPolygon::MultiPolygon(std::vector<Polygon> polys) : polygons(polys) { }

    std::unique_ptr<Geometry> MultiPolygon::clone() const  {
        auto multiPolygon = std::make_unique<MultiPolygon>(polygons);
        multiPolygon->setSrid(getSrid());
        return multiPolygon;
    }

    GeometryType MultiPolygon::getType() const {
        return GeometryType::MULTIPOLYGON;
    }

    Dimension MultiPolygon::getDimension() const {
        if (polygons.size() == 0) {
            return Dimension::Two;
        } else {
            return polygons[0].getDimension();
        }
    }

     bool MultiPolygon::isEmpty() const {
        return polygons.empty();
    }

    std::string MultiPolygon::wkt() const {
        std::stringstream str;
        str << "MULTIPOLYGON ";
        if (std::size(polygons) == 0) {
           str << " EMPTY";     
        } else {
            str << "(";
            bool firstPolygon = true;
            for(auto p : polygons) {
                if (firstPolygon != true) {
                    str << ", ";
                }
                firstPolygon = false;
                str << "(";
                bool firstRing = true;
                for(auto r : p.getLinearRings()) {
                    if (firstRing != true) {
                        str << ", ";
                    }
                    firstRing = false;
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
                str << ")";
            }
        }
        str <<  ")";
        return str.str();
    }

    std::vector<Polygon> MultiPolygon::getPolygons() const {
        return polygons;
    }

}