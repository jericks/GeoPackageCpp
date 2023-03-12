#pragma once

#include <iostream>
#include <memory>
#include "Dimension.hpp"

#include "Point.hpp"
#include "Polygon.hpp"
#include "Geometry.hpp"
#include "LineString.hpp"
#include "LinearRing.hpp"
#include "MultiPoint.hpp"
#include "MultiPolygon.hpp"
#include "GeometryCollection.hpp"
#include "MultiLineString.hpp"


namespace geopackage {

    class Bounds {

        private:

            Point min;
            
            Point max;

            static Bounds getBounds(const std::vector<Point>& points);

            static Bounds getBounds(const std::vector<Bounds>& bounds);

        public:

            Bounds(Point min, Point max);

            Bounds(double minX, double minY, double maxX, double maxY);

            Bounds(double minX, double minY, double minZ, double minM, double maxX, double maxY, double maxZ, double maxM);

            double getMinX() const;

            double getMinY() const;

            double getMinZ() const;

            double getMinM() const;

            double getMaxX() const;

            double getMaxY() const;

            double getMaxZ() const;

            double getMaxM() const;

            Dimension getDimension() const;

            std::unique_ptr<Polygon> toPolygon() const;

            static Bounds getBounds(Geometry* geometry);

    };

    std::ostream& operator << (std::ostream& os, const Bounds& bounds);

}