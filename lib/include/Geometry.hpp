#pragma once

#include <iostream>
#include <string>
#include <memory>
#include "GeometryType.hpp"

namespace geopackage {

    class Geometry {
        public:
            virtual std::string wkt() const = 0;
            virtual ~Geometry() = default;
            virtual std::unique_ptr<Geometry> clone() const = 0;
            virtual GeometryType getType() const = 0;
    };

    std::ostream& operator << (std::ostream& os, const Geometry& geometry);

}