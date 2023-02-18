#pragma once

#include <vector>
#include <sstream>
#include <iomanip>
#include "Geometry.hpp"
#include "Point.hpp"
#include "LineString.hpp"
#include "Polygon.hpp"
#include "MultiPoint.hpp"
#include "MultiLineString.hpp"
#include "MultiPolygon.hpp"
#include "GeometryCollection.hpp"

namespace geopackage {

    namespace wkb {
        
        enum class Type {
            WKB, EWKB
        };

        enum class Endian {
            BIG, LITTE
        };

    }


    class WKBWriter {

        public:

            std::vector<std::byte> write(Geometry* geometry);

            std::string writeToHex(Geometry* geometry);

        private:

            wkb::Endian endian = wkb::Endian::BIG;

            wkb::Type type = wkb::Type::WKB;

            void putByteOrder(wkb::Endian byteOrder, std::vector<std::byte>& bytes);

            void putGeometryType(GeometryType geometryType, std::vector<std::byte>& bytes);

            void putGeometry(Geometry* geometry, std::vector<std::byte>& bytes);

            void putPoint(const Point* point, std::vector<std::byte>& bytes);

            void putPoints(const std::vector<Point> points, std::vector<std::byte>& bytes);

            void putLineString(const LineString* line, std::vector<std::byte>& bytes);

            void putPolygon(const Polygon* polygon, std::vector<std::byte>& bytes);

            void putMultiPoint(const MultiPoint* multiPoint, std::vector<std::byte>& bytes);

            void putMultiLineString(const MultiLineString* multiLineString, std::vector<std::byte>& bytes);

            void putMultiPolygon(const MultiPolygon* multiPolygon, std::vector<std::byte>& bytes);

            void putGeometryCollection(GeometryCollection* geometryCollection, std::vector<std::byte>& bytes);

            void putInt(int value, std::vector<std::byte>& bytes);

            void putLong(long value, std::vector<std::byte>& bytes);

            void putDouble(double value, std::vector<std::byte>& bytes);

            std::string toHexString(std::vector<std::byte>& bytes);

    };

    
}