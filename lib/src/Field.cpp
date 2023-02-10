#include "Field.hpp"

namespace geopackage {

    Field::Field(std::string n, FieldType t) : name(n), type(t) {}

    std::string Field::getName() const {
        return name;
    }
    FieldType Field::getType() const {
        return type;
    }

    std::ostream& operator << (std::ostream& os, const Field& field) {
        os << "Field(" 
            << "name=" << field.getName() 
            << ", type=" << field.getType() 
            << ")";
        return os;
    }

    Field Field::createStringField(std::string name) {
        return Field {name, FieldType::String};
    }

    Field Field::createIntegerField(std::string name) {
       return Field {name, FieldType::Integer};     
    }
    Field Field::createDoubleField(std::string name) {
        return Field {name, FieldType::Double};
    }

    Field Field::createBooleanField(std::string name) {
        return Field {name, FieldType::Boolean};
    }

    Field Field::createBlobField(std::string name) {
        return Field {name, FieldType::Blob};
    }

}