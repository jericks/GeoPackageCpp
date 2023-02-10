#pragma once

#include <string>
#include <iostream>
#include "FieldType.hpp"

namespace geopackage {
    class Field {
        private:
            std::string name;
            FieldType type;
        public:
            Field(std::string n, FieldType t);
            std::string getName() const;
            FieldType getType() const;
            static Field createStringField(std::string name);
            static Field createIntegerField(std::string name);
            static Field createDoubleField(std::string name);
            static Field createBooleanField(std::string name);
            static Field createBlobField(std::string name);
    };
    std::ostream& operator << (std::ostream& os, const Field& field);
}