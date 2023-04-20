#include "MultiPoint.hpp"

namespace geopackage {

    MultiPoint::MultiPoint(std::vector<Point> pts) : points(pts) { }

    std::unique_ptr<Geometry> MultiPoint::clone() const  {
        auto multiPoint = std::make_unique<MultiPoint>(points);
        multiPoint->setSrid(getSrid());
        return multiPoint;
    }

    GeometryType MultiPoint::getType() const {
        return GeometryType::MULTIPOINT;
    }

    Dimension MultiPoint::getDimension() const {
        if (points.size() == 0) {
            return Dimension::Two;
        } else {
            return points[0].getDimension();
        }
    }

     bool MultiPoint::isEmpty() const {
        return points.empty();
    }

    std::string MultiPoint::wkt() const {
        return WKTWriter{}.write(this);
    }

    std::vector<Point> MultiPoint::getPoints() const {
        return points;
    }

}