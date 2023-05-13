#include "GeometryField.hpp"

namespace geopackage {

    GeometryField::GeometryField(std::string n, GeometryType t, int srsId) : name(n), type(t), dimension(Dimension::Two), srsId(srsId) {}

    GeometryField::GeometryField(std::string n, GeometryType t, Dimension d, int srsId) : name(n), type(t), dimension(d), srsId(srsId) {}

    std::string GeometryField::getName() const {
        return name;
    }
    
    GeometryType GeometryField::getType() const {
        return type;
    }

    Dimension GeometryField::getDimension() const {
        return dimension;
    }

    int GeometryField::getSrsId() const {
        return srsId;
    }

    std::ostream& operator << (std::ostream& os, const GeometryField& field) {
        os << "GeometryField(" 
            << "name=" << field.getName() 
            << ", type=" << geometrytype::toString(field.getType())
            << ", dimension=" << dimension::toString(field.getDimension())
            << ", srsId=" << field.getSrsId()
            << ")";
        return os;
    }

}