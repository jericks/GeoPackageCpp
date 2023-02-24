#pragma once

#include "LineString.hpp"
#include <sstream>
#include <vector>

namespace geopackage {

    class MultiLineString : public Geometry {

        private:

            std::vector<LineString> lines;

        public:

            MultiLineString(std::vector<LineString> lines);

            virtual Dimension getDimension() const override;

            virtual std::string wkt() const override;

            virtual std::unique_ptr<Geometry> clone() const override;

            std::vector<LineString> getLineStrings() const;

            virtual GeometryType getType() const override;

            virtual bool isEmpty() const override;

    };

}