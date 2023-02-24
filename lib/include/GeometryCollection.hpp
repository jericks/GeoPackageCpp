#pragma once

#include "Point.hpp"
#include <sstream>
#include <vector>

namespace geopackage {

    class GeometryCollection : public Geometry {

        private:

            std::vector<std::unique_ptr<Geometry>> geometries = {};

        public:

            GeometryCollection(std::vector<std::unique_ptr<Geometry>> && geoms);

            virtual Dimension getDimension() const override;

            virtual std::string wkt() const override;

            virtual std::unique_ptr<Geometry> clone() const override;

            std::vector<std::unique_ptr<Geometry>>& getGeometries();

            int getNumberOfGeometries() const;

            virtual GeometryType getType() const override;

            virtual bool isEmpty() const override;

    };

}