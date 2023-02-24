#pragma once

#include "LinearRing.hpp"
#include <sstream>
#include <vector>

namespace geopackage {

    class Polygon : public Geometry {

        private:

            std::vector<LinearRing> rings;

        public:

            Polygon(LinearRing ring);

            Polygon(std::vector<LinearRing> rings);

            virtual Dimension getDimension() const override;

            virtual std::string wkt() const override;

            virtual std::unique_ptr<Geometry> clone() const override;

            std::vector<LinearRing> getLinearRings() const;

            virtual GeometryType getType() const override;

            virtual bool isEmpty() const override;

    };


}