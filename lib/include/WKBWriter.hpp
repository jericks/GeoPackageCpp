#pragma once

#include <vector>
#include <sstream>
#include "Geometry.hpp"
#include "Point.hpp"
#include "LineString.hpp"
#include "Polygon.hpp"
#include "MultiPoint.hpp"
#include "MultiLineString.hpp"
#include "MultiPolygon.hpp"
#include "GeometryCollection.hpp"
#include "Endian.hpp"
#include "Bytes.hpp"

namespace geopackage {

    namespace wkb {
        
        enum class Type {
            WKB, EWKB
        };

    }


    class WKBWriter {

        public:

            WKBWriter();

            WKBWriter(wkb::Type type, Endian endian);

            std::vector<std::byte> write(Geometry* geometry);

            std::string writeToHex(Geometry* geometry);

        private:

            Endian endian = Endian::BIG;

            wkb::Type type = wkb::Type::WKB;

            Bytes writeToBytes(Geometry* geometry);

            void putByteOrder(Endian byteOrder, Bytes& bytes);

            void putGeometryType(GeometryType geometryType, Dimension dimension, std::string srid, Bytes& bytes);

            void putSrid(std::string srid, Bytes& bytes);

            void putGeometry(Geometry* geometry, Bytes& bytes);

            void putPoint(const Point* point, Bytes& bytes);

            void putPoints(const std::vector<Point> points, Bytes& bytes);

            void putLineString(const LineString* line, Bytes& bytes);

            void putPolygon(const Polygon* polygon, Bytes& bytes);

            void putMultiPoint(const MultiPoint* multiPoint, Bytes& bytes);

            void putMultiLineString(const MultiLineString* multiLineString, Bytes& bytes);

            void putMultiPolygon(const MultiPolygon* multiPolygon, Bytes& bytes);

            void putGeometryCollection(GeometryCollection* geometryCollection, Bytes& bytes);

    };

    
}