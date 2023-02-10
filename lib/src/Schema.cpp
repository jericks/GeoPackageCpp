#include "Schema.hpp"

namespace geopackage {

    Schema::Schema(std::string name, GeometryField gf, std::vector<Field> flds) : name(name), geometryField(gf), fields(flds) {}

    std::string Schema::getName() const {
        return name;
    }

    GeometryField Schema::getGeometryField() const {
        return geometryField;
    }

    std::vector<Field> Schema::getFields() const {
        return fields;
    }

    std::ostream& operator << (std::ostream& os, const Schema& schema) {
        os << "Schema(";
        os << "name = " << schema.getName();
        os << ", geometryField = " << schema.getGeometryField();
        os << ", fields = [";
        for (Field fld : schema.getFields()) {
            os << " "  << fld;
        }
        os << "])";
        return os;
    }


}