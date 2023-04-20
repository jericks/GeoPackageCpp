#include "GeometryCollection.hpp"

namespace geopackage {

    GeometryCollection::GeometryCollection(std::vector<std::unique_ptr<Geometry>> && geoms) :  geometries(std::move(geoms)) { }

    std::unique_ptr<Geometry> GeometryCollection::clone() const  {
         std::vector<std::unique_ptr<Geometry>> clonedGeometries;
         for(auto & g : geometries) {
            clonedGeometries.push_back(g->clone());
         }
        auto gc = std::make_unique<GeometryCollection>(std::move(clonedGeometries));
        gc->setSrid(getSrid());
        return gc;
    }

    GeometryType GeometryCollection::getType() const {
        return GeometryType::GEOMETRYCOLLECTION;
    }

    Dimension GeometryCollection::getDimension() const {
        if (geometries.size() == 0) {
            return Dimension::Two;
        } else {
            return geometries[0].get()->getDimension();
        }
    }

    bool GeometryCollection::isEmpty() const {
        return geometries.empty();
    }

    std::string GeometryCollection::wkt() const {
        return WKTWriter{}.write(this);
    }

    std::vector<std::unique_ptr<Geometry>>&  GeometryCollection::getGeometries() {
        return geometries;
    }

    int GeometryCollection::getNumberOfGeometries() const {
        return geometries.size();
    }    
}