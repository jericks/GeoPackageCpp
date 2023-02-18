#pragma once

#include "Point.hpp"
#include <sstream>
#include <vector>

namespace geopackage {

    class MultiPoint : public Geometry {

        private:

            std::vector<Point> points;

        public:

            MultiPoint(std::vector<Point> points);

            virtual std::string wkt() const override;

            virtual std::unique_ptr<Geometry> clone() const override;

            std::vector<Point> getPoints() const;

            virtual GeometryType getType() const override;

    };

}