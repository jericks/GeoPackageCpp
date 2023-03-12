#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <optional>
#include "Geometry.hpp"
#include "Bounds.hpp"
#include "BinaryType.hpp"
#include "EnvelopeType.hpp"
#include "Flag.hpp"
#include "WKBReader.hpp"
#include "Endian.hpp"
#include "Bytes.hpp"

namespace geopackage {

    class GeoPackageGeometryReader {


        public:

            std::unique_ptr<Geometry> read(std::vector<std::byte>);


    };   

}