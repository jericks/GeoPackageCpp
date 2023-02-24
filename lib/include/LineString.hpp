#pragma once

#include "Geometry.hpp"
#include "Point.hpp"
#include "GeometryType.hpp"
#include <sstream>
#include <vector>

namespace geopackage {

    class LineString : public Geometry {

        private:

            std::vector<Point> points;

        public:

            LineString(std::vector<Point> points);

            virtual Dimension getDimension() const override;

            virtual std::string wkt() const override;

            virtual std::unique_ptr<Geometry> clone() const override;

            std::vector<Point> getPoints() const;

            virtual GeometryType getType() const override;

            virtual bool isEmpty() const override;

    };

}