#include "LineString.hpp"

namespace geopackage {

    LineString:: LineString(std::vector<Point> pts) : points(pts) { }

    std::unique_ptr<Geometry> LineString::clone() const  {
        return std::make_unique<LineString>(points);
    }

    GeometryType LineString::getType() const {
        return GeometryType::LINESTRING;
    }

    std::string LineString::wkt() const {
        std::stringstream str;
        str << "LINESTRING ";
        if (std::size(points) == 0) {
            str << "EMPTY";
        } else {
            str << "(";
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

    std::vector<Point> LineString::getPoints() const {
        return points;
    }

}