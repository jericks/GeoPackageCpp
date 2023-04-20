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
       return WKTWriter{}.write(this);
    }

    std::vector<Polygon> MultiPolygon::getPolygons() const {
        return polygons;
    }

}