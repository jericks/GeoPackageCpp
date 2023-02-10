#pragma once

#include <string>
#include <iostream>
#include "GeometryType.hpp"

namespace geopackage {
    class GeometryField {
        private:
            std::string name;
            GeometryType type;
        public:
            GeometryField(std::string n, GeometryType t);
            std::string getName() const;
            GeometryType getType() const;
    };
    std::ostream& operator << (std::ostream& os, const GeometryField& field);
}