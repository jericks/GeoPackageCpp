#include "Feature.hpp"

namespace geopackage {

    Feature::Feature(std::unique_ptr<Geometry> geom, std::map<std::string, std::any> attr): geometry(geom->clone()), attributes(attr) {}

    Feature::Feature(int id, std::unique_ptr<Geometry> geom, std::map<std::string, std::any> attr): id(id), geometry(geom->clone()), attributes(attr) {}

    Feature::Feature(Feature const &other) : id(other.id), geometry(other.geometry->clone()), attributes(other.attributes) {}

    std::optional<int> Feature::getId() const {
        return id;
    }

    Geometry* Feature::getGeometry() const {
        return geometry.get();
    }

    std::map<std::string, std::any> Feature::getAttributes() const {
        return attributes;
    }

    Feature& Feature::setAttribute(std::string name, std::any value) {
        this->attributes[name] = value;
        return *this;
    }

    Feature& Feature::setGeometry(std::unique_ptr<Geometry> geometry) {
        this->geometry.release();
        this->geometry = geometry->clone();
        return *this;
    }
    
    std::ostream& operator << (std::ostream& os, const Feature& feature) {
        os << "Feature(" << feature.getGeometry()->wkt() << ")";
        return os;
    }

}