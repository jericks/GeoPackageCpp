#include "WKTWriter.hpp"
#include "Geometry.hpp"
#include "Point.hpp"
#include "LineString.hpp"
#include "Polygon.hpp"
#include "MultiPoint.hpp"
#include "MultiLineString.hpp"
#include "MultiPolygon.hpp"
#include "GeometryCollection.hpp"

namespace geopackage {

    std::string WKTWriter::write(Geometry* geometry) const {
        GeometryType geometryType = geometry->getType();
        if (geometryType == GeometryType::POINT) {
            Point* pt = static_cast<Point *>(geometry);
            return writePoint(pt);
        } else if (geometryType == GeometryType::LINESTRING) {
            LineString* line = static_cast<LineString *>(geometry);
            return writeLineString(line);
        } else if (geometryType == GeometryType::POLYGON) {
            Polygon* polygon = static_cast<Polygon *>(geometry);
            return writePolygon(polygon);
        } else if (geometryType == GeometryType::MULTIPOINT) {
            MultiPoint* pts = static_cast<MultiPoint *>(geometry);
            return writeMultiPoint(pts);
        } else if (geometryType == GeometryType::MULTILINESTRING) {
            MultiLineString* lines = static_cast<MultiLineString *>(geometry);
            return writeMultiLineString(lines);
        } else if (geometryType == GeometryType::MULTIPOLYGON) {
            MultiPolygon* polygons = static_cast<MultiPolygon *>(geometry);
            return writeMultiPolygon(polygons);
        } else if (geometryType == GeometryType::GEOMETRYCOLLECTION) {
            GeometryCollection* geometries = static_cast<GeometryCollection *>(geometry);
            return writeGeometryCollection(geometries);
        } else {
            return "";
        }
    }

    std::string WKTWriter::write(const Geometry* geometry) const {
        return write(const_cast<Geometry *>(geometry));
    }

    std::string WKTWriter::writePoint(Point* point) const {
       std::stringstream str;
       double x = point->getX();
       double y = point->getY();
       double z = point->getZ();
       double m = point->getM();
        if (isnan(x) && isnan(y)) {
            str << "POINT EMPTY";
        } else {
            str << "POINT ";
            if (!isnan(z) && !isnan(m)) {
                str << "ZM ";    
            } else if (!isnan(z)) {
                str << "Z ";    
            } else if (!isnan(m)) {
                str << "M ";    
            }
            str << "(";
            str << x << " ";
            str << y;
            if (!isnan(z)) {
                str << " " << z;
            }
            if (!isnan(m)) {
                str << " " << m;
            }
            str << ")";
            
        }
        return str.str();
    }

    std::string WKTWriter::writeLineString(LineString* lineString) const {
        std::stringstream str;
        str << "LINESTRING ";
        if (std::size(lineString->getPoints()) == 0) {
            str << "EMPTY";
        } else {
            str << "(";
            bool firstTime = true;
            for(auto p : lineString->getPoints()) {
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

    std::string WKTWriter::writePolygon(Polygon* polygon) const {
        std::stringstream str;
        str << "POLYGON ";
        if (std::size(polygon->getLinearRings()) == 0) {
            str << "EMPTY";    
        } else {
            str << "(";
            bool firstLinearRing = true;
            for(auto r : polygon->getLinearRings()) {
                if (firstLinearRing != true) {
                    str << ", ";
                }
                firstLinearRing = false;
                str << "(";
                bool firstTime = true;
                for(auto p : r.getPoints()) {
                    if (firstTime != true) {
                        str << ", ";
                    }
                    firstTime = false;
                    str << p.getX() << " " << p.getY();
                }
                str << ")";
            }
            str <<  ")";
        }
        return str.str();
    }

    std::string WKTWriter::writeMultiPoint(MultiPoint* multiPoint) const {
        std::stringstream str;
        str << "MULTIPOINT ";
        if (std::size(multiPoint->getPoints()) == 0) {
            str <<  "EMPTY";
        } else {
            str <<  "(";
            bool firstTime = true;
            for(auto p : multiPoint->getPoints()) {
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

    std::string WKTWriter::writeMultiLineString(MultiLineString* multiLineString) const {
        std::stringstream str;
        str << "MULTILINESTRING ";
        if (std::size(multiLineString->getLineStrings()) == 0) {
            str <<  "EMPTY";
        } else {
            str <<  "(";
            bool firstLine = true;
            for(auto l : multiLineString->getLineStrings()) {
                if (firstLine != true) {
                    str << ", ";
                }
                firstLine = false;
                bool firstTime = true;
                str << "(";
                for(auto p : l.getPoints()) {
                    if (firstTime != true) {
                        str << ", ";
                    }
                    firstTime = false;
                    str << p.getX() << " " << p.getY();
                }
                str << ")";
            }
            str <<  ")";
        }
        return str.str();
    }

    std::string WKTWriter::writeMultiPolygon(MultiPolygon* multiPolygon) const {
         std::stringstream str;
        str << "MULTIPOLYGON ";
        if (std::size(multiPolygon->getPolygons()) == 0) {
           str << " EMPTY";     
        } else {
            str << "(";
            bool firstPolygon = true;
            for(auto p : multiPolygon->getPolygons()) {
                if (firstPolygon != true) {
                    str << ", ";
                }
                firstPolygon = false;
                str << "(";
                bool firstRing = true;
                for(auto r : p.getLinearRings()) {
                    if (firstRing != true) {
                        str << ", ";
                    }
                    firstRing = false;
                    str << "(";
                    bool firstTime = true;
                    for(auto p : r.getPoints()) {
                        if (firstTime != true) {
                            str << ", ";
                        }
                        firstTime = false;
                        str << p.getX() << " " << p.getY();
                    }
                    str << ")";
                }
                str << ")";
            }
        }
        str <<  ")";
        return str.str();
    }

    std::string WKTWriter::writeGeometryCollection(GeometryCollection* geometryCollection) const {
        std::stringstream str;
        str << "GEOMETRYCOLLECTION ";
        std::vector<std::unique_ptr<Geometry>>& geometries = geometryCollection->getGeometries();
        if (std::size(geometries) == 0) {
            str <<  "EMPTY";
        } else {
            str <<  "(";
            bool firstTime = true;
            for(auto & g : geometries) {
                if (firstTime != true) {
                    str << ", ";
                }
                firstTime = false;
                str << g->wkt();
            }
            str <<  ")";
        }
        return str.str();
    }

}