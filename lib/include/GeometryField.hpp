#pragma once

#include <string>
#include <iostream>
#include "GeometryType.hpp"

namespace geopackage {
    class GeometryField {
        private:
            std::string name;
            GeometryType type;
            int srsId;
        public:
            GeometryField(std::string n, GeometryType t, int srsId);
            std::string getName() const;
            GeometryType getType() const;
            int getSrsId() const;
    };
    std::ostream& operator << (std::ostream& os, const GeometryField& field);
}