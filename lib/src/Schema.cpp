#include "Schema.hpp"

namespace geopackage {

    Schema::Schema(std::string name, std::string key, GeometryField gf, std::vector<Field> flds) : name(name), key(key), geometryField(gf), fields(flds) {}

    std::string Schema::getName() const {
        return name;
    }

    std::string Schema::getKey() const {
        return key;
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
        os << ", key = " << schema.getKey();
        os << ", geometryField = " << schema.getGeometryField();
        os << ", fields = [";
        for (Field fld : schema.getFields()) {
            os << " "  << fld;
        }
        os << "])";
        return os;
    }


}