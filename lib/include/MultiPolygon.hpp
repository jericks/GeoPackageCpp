#pragma once

#include "Polygon.hpp"
#include <sstream>
#include <vector>

namespace geopackage {

    class MultiPolygon : public Geometry {

        private:

            std::vector<Polygon> polygons;

        public:

            MultiPolygon(std::vector<Polygon> polygons);

            virtual Dimension getDimension() const override;

            virtual std::string wkt() const override;

            virtual std::unique_ptr<Geometry> clone() const override;

            std::vector<Polygon> getPolygons() const;

            virtual GeometryType getType() const override;

            virtual bool isEmpty() const override;

    };

}