#include "LinearRing.hpp"

namespace geopackage {

    LinearRing:: LinearRing(std::vector<Point> pts) : points(pts) {}

    std::unique_ptr<Geometry> LinearRing::clone() const  {
        return std::make_unique<LinearRing>(points);
    }

    GeometryType LinearRing::getType() const {
        return GeometryType::LINEARRING;
    }

    Dimension LinearRing::getDimension() const {
        if (points.size() == 0) {
            return Dimension::Two;
        } else {
            return points[0].getDimension();
        }
    }

    bool LinearRing::isEmpty() const {
        return points.empty();
    }

    std::string LinearRing::wkt() const {
        std::stringstream str;
        str << "LINEARRING ";
        if (std::size(points) == 0) {
            str <<  "EMPTY";
        } else {
            str <<  "(";
            bool firstTime = true;
            for(auto p : points) {
                if (firstTime != true) {
                    str << ", ";
                }
                firstTime = false;
                str << p.getX() << " " << p.getY();
            }
            str <<  ")";
        }
        return str.str();
    }

    std::vector<Point> LinearRing::getPoints() const {
        return points;
    }

}