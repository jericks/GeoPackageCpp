#pragma once

#include <iostream>

namespace geopackage {

    enum class BinaryType {
        Standard, Extended
    };

    namespace binarytype {

        std::string toString(BinaryType binaryType);

        int getValue(BinaryType binaryType);

        std::byte getByte(BinaryType binaryType);

    }

    std::ostream& operator << (std::ostream& os, const BinaryType& binaryType);

}