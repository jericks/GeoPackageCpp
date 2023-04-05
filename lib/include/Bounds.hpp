#pragma once

#include <iostream>
#include <memory>
#include <sstream>
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

            static Bounds xy(double minX, double minY, double maxX, double maxY);

            static Bounds xym(double minX, double minY, double minM, double maxX, double maxY, double maxM);
            
            static Bounds xyz(double minX, double minY, double minZ, double maxX, double maxY, double maxZ);
            
            static Bounds xyzm(double minX, double minY, double minZ, double minM, double maxX, double maxY, double maxZ, double maxM);
            
            static Bounds fromString(std::string str);
    };

    std::ostream& operator << (std::ostream& os, const Bounds& bounds);

}