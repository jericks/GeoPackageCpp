#pragma once

#include <string>
#include <memory>

namespace geopackage {

    class Geometry;
    class Point;
    class LineString;
    class Polygon;
    class MultiPoint;
    class MultiLineString;
    class MultiPolygon;
    class GeometryCollection;

    class WKTWriter {
        
        private:

            std::string writePoint(Point* point) const;

            std::string writeLineString(LineString* lineString) const; 

            std::string writePolygon(Polygon* polygon) const; 

            std::string writeMultiPoint(MultiPoint* multiPoint) const;

            std::string writeMultiLineString(MultiLineString* multiLineString) const; 

            std::string writeMultiPolygon(MultiPolygon* multiPolygon) const; 

            std::string writeGeometryCollection(GeometryCollection* geometryCollection) const; 

        public:

            std::string write(Geometry* geometry) const;

            std::string write(const Geometry* geometry) const;

    };

}