#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include "Geometry.hpp"
#include "Bounds.hpp"
#include "BinaryType.hpp"
#include "EnvelopeType.hpp"
#include "Flag.hpp"
#include "WKBWriter.hpp"
#include "Endian.hpp"
#include "Bytes.hpp"

namespace geopackage {

    class GeoPackageGeometryWriter {


        public:

            std::vector<std::byte> write(Geometry* geometry);

            std::string writeToHex(Geometry* geometry);

        private:

            int version = 0;

            BinaryType binaryType = BinaryType::Standard;

            EnvelopeType envelopeType = EnvelopeType::Envelope;

            Endian endian = Endian::BIG;

            WKBWriter wkbWriter {wkb::Type::EWKB, endian};

            Bytes writeToBytes(Geometry* geometry);

    };

    

}