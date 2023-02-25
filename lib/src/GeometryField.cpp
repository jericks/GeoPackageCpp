#include "GeometryField.hpp"

namespace geopackage {

    GeometryField::GeometryField(std::string n, GeometryType t, int srsId) : name(n), type(t), srsId(srsId) {}

    std::string GeometryField::getName() const {
        return name;
    }
    GeometryType GeometryField::getType() const {
        return type;
    }

    int GeometryField::getSrsId() const {
        return srsId;
    }

    std::ostream& operator << (std::ostream& os, const GeometryField& field) {
        os << "GeometryField(" 
            << "name=" << field.getName() 
            << ", type=" << geometrytype::toString(field.getType())
            << ", srsId=" << field.getSrsId()
            << ")";
        return os;
    }

}