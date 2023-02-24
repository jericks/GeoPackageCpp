#include "Bounds.hpp"

namespace geopackage {

    Bounds::Bounds(Point min, Point max) : min(min), max(max) {}

    Bounds::Bounds(double minX, double minY, double maxX, double maxY) : min(Point{minX, minY}), max(Point{maxX, maxY}) {}

    double Bounds::getMinX() const {
        return min.getX();
    }

    double Bounds::getMinY() const {
        return min.getY();
    }

    double Bounds::getMinZ() const {
        return min.getZ();
    }

    double Bounds::getMinM() const {
        return min.getM();
    }

    double Bounds::getMaxX() const {
        return max.getX();
    }

    double Bounds::getMaxY() const {
        return max.getY();
    }

    double Bounds::getMaxZ() const {
        return max.getZ();
    }

    double Bounds::getMaxM() const {
        return max.getM();
    }

    Dimension Bounds::getDimension() const {
        return min.getDimension();
    }

    std::unique_ptr<Polygon> Bounds::toPolygon() const {
        LinearRing ring {{
            {min.getX(),min.getY()}, {max.getX(), min.getY()}, {max.getX(),max.getY()}, {min.getX(), min.getY()}
        }};
        Polygon polygon {{ring}};
        return std::make_unique<Polygon>(polygon);
    }

    std::ostream& operator << (std::ostream& os, const Bounds& b) {
        os << "BOUNDS (" << b.getMinX() << ", " << b.getMinX()  << ", " << b.getMaxX() << ", " << b.getMaxY() << ")";
        return os;
    }

    Bounds Bounds::getBounds(Geometry* geometry) {
        GeometryType type = geometry->getType();
        if (type == GeometryType::POINT) {
            Point* pt = static_cast<Point *>(geometry);
            return Bounds{pt->getX(), pt->getY(), pt->getX(), pt->getY()};
        } else if (type == GeometryType::LINESTRING) {
            LineString* line = static_cast<LineString *>(geometry);
            return Bounds::getBounds(line->getPoints());
        } else if (type == GeometryType::LINEARRING) {
            LinearRing* ring = static_cast<LinearRing *>(geometry);
            return Bounds::getBounds(ring->getPoints());
        } else if (type == GeometryType::POLYGON) {
            Polygon* polygon = static_cast<Polygon *>(geometry);
            std::vector<Bounds> bounds;
            for(auto ring : polygon->getLinearRings()) {
                bounds.push_back(Bounds::getBounds(ring.getPoints()));
            }
            return Bounds::getBounds(bounds);
        } else if (type == GeometryType::MULTIPOINT) {
            MultiPoint* multiPoint = static_cast<MultiPoint *>(geometry);
            return Bounds::getBounds(multiPoint->getPoints());
        } else if (type == GeometryType::MULTILINESTRING) {
            MultiLineString* lines = static_cast<MultiLineString *>(geometry);
            std::vector<Bounds> bounds;
            for(auto line : lines->getLineStrings()) {
                bounds.push_back(Bounds::getBounds(line.getPoints()));
            }
            return Bounds::getBounds(bounds);
        } else if (type == GeometryType::MULTIPOLYGON) {
            MultiPolygon* polygons = static_cast<MultiPolygon *>(geometry);
            std::vector<Bounds> bounds;
            for(auto polygon : polygons->getPolygons()) {
                bounds.push_back(Bounds::getBounds(&polygon));
            }
            return Bounds::getBounds(bounds);
        } else if (type == GeometryType::GEOMETRYCOLLECTION) {
            GeometryCollection* geometries = static_cast<GeometryCollection *>(geometry);
            std::vector<Bounds> bounds;
            for(auto & geom : geometries->getGeometries()) {
                bounds.push_back(Bounds::getBounds(geom.get()));
            }
            return Bounds::getBounds(bounds);
        } else {
            return Bounds{0,0,0,0};
        }
    }

    Bounds Bounds::getBounds(const std::vector<Point>& points) {
        double minX;
        double minY;
        double maxX;
        double maxY;
        for(auto p : points) {
            minX = std::min(minX, p.getX());
            maxX = std::max(maxX, p.getX());
            minY = std::min(minY, p.getY());
            maxY = std::max(maxY, p.getY());
        }
        return Bounds{minX, minY, maxX, maxY};
    }

    Bounds Bounds::getBounds(const std::vector<Bounds>& bounds) {
        double minX;
        double minY;
        double maxX;
        double maxY;
        for(auto b : bounds) {
            minX = std::min(minX, b.getMinX());
            maxX = std::max(maxX, b.getMaxX());
            minY = std::min(minY, b.getMinY());
            maxY = std::max(maxY, b.getMaxY());
        }
        return Bounds{minX, minY, maxX, maxY};
    }

}