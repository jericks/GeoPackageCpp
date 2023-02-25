#pragma once

#include <string>
#include <vector>
#include "GeometryField.hpp"
#include "Field.hpp"

namespace geopackage {
    class Schema {
        private:
            std::string name;
            std::string key;
            GeometryField geometryField;
            std::vector<Field> fields;
        public:
            Schema(std::string name, std::string key, GeometryField geometryField, std::vector<Field> fields);
            std::string getName() const;
            std::string getKey() const;
            GeometryField getGeometryField() const;
            std::vector<Field> getFields() const;
    };
    std::ostream& operator << (std::ostream& os, const Schema& schema);
}