#include "Bounds.hpp"

namespace geopackage {

    Bounds::Bounds(Point min, Point max) : min(min), max(max) {}

    Bounds::Bounds(double minX, double minY, double maxX, double maxY) : min(Point{minX, minY}), max(Point{maxX, maxY}) {}

    Bounds::Bounds(double minX, double minY, double minZ, double minM, double maxX, double maxY, double maxZ, double maxM)
        : min(Point{minX, minY, minZ, minM}), max(Point{maxX, maxY, maxZ, maxM}) {}

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
        os << "BOUNDS ";
        Dimension dim = b.getDimension();
        if (dim == Dimension::ThreeMeasured) {
            os << "ZM";
        } else if (dim == Dimension::Three) {
            os << "Z";
        } else if (dim == Dimension::TwoMeasured) {
            os << "M";
        }
        os << "(";
        os << b.getMinX() << ", " << b.getMinY();
        if (dimension::hasZ(dim)) {
            os << ", " << b.getMinZ();
        }
        if (dimension::hasM(dim)) {
            os << ", " << b.getMinM();
        }
        os << ", " << b.getMaxX() << ", " << b.getMaxY();
        if (dimension::hasZ(dim)) {
            os << ", " << b.getMaxZ();
        }
        if (dimension::hasM(dim)) {
            os << ", " << b.getMaxM();
        }
        os << ")";
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
        double minX = NAN;
        double minY = NAN;
        double maxX = NAN;
        double maxY = NAN;
        for(auto p : points) {
            minX = isnan(minX) ? p.getX() : std::min(minX, p.getX());
            maxX = isnan(maxX) ? p.getX() : std::max(maxX, p.getX());
            minY = isnan(minY) ? p.getY() : std::min(minY, p.getY());
            maxY = isnan(maxY) ? p.getY() : std::max(maxY, p.getY());
        }
        return Bounds{minX, minY, maxX, maxY};
    }

    Bounds Bounds::getBounds(const std::vector<Bounds>& bounds) {
        double minX = NAN;
        double minY = NAN;
        double maxX = NAN;
        double maxY = NAN;
        for(auto b : bounds) {
            minX = isnan(minX) ? b.getMinX() : std::min(minX, b.getMinX());
            maxX = isnan(maxX) ? b.getMaxX() : std::max(maxX, b.getMaxX());
            minY = isnan(minY) ? b.getMinY() : std::min(minY, b.getMinY());
            maxY = isnan(maxY) ? b.getMaxY() : std::max(maxY, b.getMaxY());
        }
        return Bounds {minX, minY, maxX, maxY};
    }

    Bounds Bounds::xy(double minX, double minY, double maxX, double maxY) {
        return Bounds{minX, minY, maxX, maxY};
    }
    Bounds Bounds::xym(double minX, double minY, double minM, double maxX, double maxY, double maxM) {
        return Bounds{minX, minY, NAN, minM, maxX, maxY, NAN, maxM};
    }
    Bounds Bounds::xyz(double minX, double minY, double minZ, double maxX, double maxY, double maxZ) {
        return Bounds{minX, minY, minZ, NAN, maxX, maxY, maxZ, NAN};
    }
    Bounds Bounds::xyzm(double minX, double minY, double minZ, double minM, double maxX, double maxY, double maxZ, double maxM) {
        return Bounds{minX, minY, minZ, minM, maxX, maxY, maxZ, maxM};
    }

    Bounds Bounds::fromString(std::string str) {
        std::vector<double> coordinates;
        std::stringstream coordinateStream(str);
        while(coordinateStream.good()) {
            std::string coordinateStr;
            getline(coordinateStream, coordinateStr, ','); 
            coordinates.push_back(std::atof(coordinateStr.c_str()));
        }
        return Bounds{coordinates[0], coordinates[1], coordinates[2], coordinates[3]};
    }

    Bounds Bounds::getGeodeticBounds() {
        return Bounds{-180,-90,180,90};
    }

    Bounds Bounds::getMercatorBounds() {
        return Bounds{-20037508.3427892,-20037508.3427892,20037508.3427892,20037508.3427892};
    }

}