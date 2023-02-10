#include "GeometryField.hpp"

namespace geopackage {

    GeometryField::GeometryField(std::string n, GeometryType t) : name(n), type(t) {}

    std::string GeometryField::getName() const {
        return name;
    }
    GeometryType GeometryField::getType() const {
        return type;
    }

    std::ostream& operator << (std::ostream& os, const GeometryField& field) {
        os << "GeometryField(" 
            << "name=" << field.getName() 
            << ", type=" << geometrytype::toString(field.getType())
            << ")";
        return os;
    }

}