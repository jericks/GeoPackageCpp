#pragma once

#include <iostream>

namespace geopackage {

    enum class Flag {
        BinaryType, GeometryEmpty, EnvelopeIndicator, Endianess
    };

    namespace flag {

        std::byte getByte(Flag flag);

    }

}