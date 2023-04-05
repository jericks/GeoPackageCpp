#pragma once

#include <string>
#include <memory>
#include <peglib.h>
#include "Geometry.hpp"
#include "Point.hpp"
#include "LineString.hpp"
#include "LinearRing.hpp"
#include "Polygon.hpp"
#include "MultiPoint.hpp"
#include "MultiLineString.hpp"
#include "MultiPolygon.hpp"
#include "GeometryCollection.hpp"

namespace geopackage {

    class WKTReader {
        
        private:

            

        public:

            std::unique_ptr<Geometry> read(std::string str);

    };

}