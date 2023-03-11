#pragma once

#include <vector>
#include "Geometry.hpp"
#include "Point.hpp"
#include "LineString.hpp"
#include "LinearRing.hpp"
#include "Polygon.hpp"
#include "MultiPoint.hpp"
#include "MultiLineString.hpp"
#include "MultiPolygon.hpp"
#include "GeometryCollection.hpp"
#include "Endian.hpp"
#include "Bytes.hpp"

namespace geopackage {

    class WKBReader {
        
        private:

            std::unique_ptr<Geometry> read(Bytes& bytes);

            std::unique_ptr<Geometry> read(Bytes& bytes, GeometryType geometryType, Dimension dimension, std::string srid);                

            Point getPoint(Bytes& bytes, Dimension dimension);

            LineString getLineString(Bytes& bytes, Dimension dimension);

            Polygon getPolygon(Bytes& bytes, Dimension dimension);

            LinearRing getLinearRing(Bytes& bytes, Dimension dimension);

            MultiPoint getMultiPoint(Bytes& bytes, Dimension dimension);

            MultiLineString getMultiLineString(Bytes& bytes, Dimension dimension);

            MultiPolygon getMultiPolygon(Bytes& bytes, Dimension dimension);

            GeometryCollection getGeometryCollection(Bytes& bytes, Dimension dimension);

        public:

            std::unique_ptr<Geometry> read(std::vector<std::byte> bytes);

    };

}