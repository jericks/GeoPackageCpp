#pragma once

#include <string>
#include <iostream>
#include "GeometryType.hpp"
#include "Dimension.hpp"

namespace geopackage {
    class GeometryField {
        private:
            std::string name;
            GeometryType type;
            Dimension dimension;
            int srsId;
            
        public:
            GeometryField(std::string n, GeometryType t, int srsId);
            GeometryField(std::string n, GeometryType t, Dimension dimension, int srsId);
            std::string getName() const;
            GeometryType getType() const;
            Dimension getDimension() const;
            int getSrsId() const;
    };
    std::ostream& operator << (std::ostream& os, const GeometryField& field);
}