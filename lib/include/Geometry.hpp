#pragma once

#include <iostream>
#include <string>
#include <memory>
#include "GeometryType.hpp"
#include "Dimension.hpp"

namespace geopackage {

    class Geometry {
        private:
            std::string srid;
        public:
            std::string getSrid() const;
            void setSrid(std::string srid);
            virtual std::string wkt() const = 0;
            virtual ~Geometry() = default;
            virtual std::unique_ptr<Geometry> clone() const = 0;
            virtual GeometryType getType() const = 0;
            virtual Dimension getDimension() const = 0;
            virtual bool isEmpty() const = 0;
    };

    std::ostream& operator << (std::ostream& os, const Geometry& geometry);

}