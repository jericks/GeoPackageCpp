#include "LineString.hpp"

namespace geopackage {

    LineString:: LineString(std::vector<Point> pts) : points(pts) { }

    std::unique_ptr<Geometry> LineString::clone() const  {
        auto line = std::make_unique<LineString>(points);
        line->setSrid(getSrid());
        return line;
    }

    GeometryType LineString::getType() const {
        return GeometryType::LINESTRING;
    }

    Dimension LineString::getDimension() const {
        if (points.size() == 0) {
            return Dimension::Two;
        } else {
            return points[0].getDimension();
        }
    }

    bool LineString::isEmpty() const {
        return points.empty();
    }

    std::string LineString::wkt() const {
        return WKTWriter{}.write(this);
    }

    std::vector<Point> LineString::getPoints() const {
        return points;
    }

}