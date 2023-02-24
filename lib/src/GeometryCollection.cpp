#include "GeometryCollection.hpp"

namespace geopackage {

    GeometryCollection::GeometryCollection(std::vector<std::unique_ptr<Geometry>> && geoms) :  geometries(std::move(geoms)) { }

    std::unique_ptr<Geometry> GeometryCollection::clone() const  {
         std::vector<std::unique_ptr<Geometry>> clonedGeometries;
         for(auto & g : geometries) {
            clonedGeometries.push_back(g->clone());
         }
        return std::make_unique<GeometryCollection>(std::move(clonedGeometries));
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
        std::stringstream str;
        str << "GEOMETRYCOLLECTION ";
        if (std::size(geometries) == 0) {
            str <<  "EMPTY";
        } else {
            str <<  "(";
            bool firstTime = true;
            for(auto & g : geometries) {
                if (firstTime != true) {
                    str << ", ";
                }
                firstTime = false;
                str << g->wkt();
            }
            str <<  ")";
        }
        return str.str();
    }

    std::vector<std::unique_ptr<Geometry>>&  GeometryCollection::getGeometries() {
        return geometries;
    }

    int GeometryCollection::getNumberOfGeometries() const {
        return geometries.size();
    }    
}