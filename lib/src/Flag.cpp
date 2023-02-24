#include "Flag.hpp"

namespace geopackage {

    namespace flag {

        std::byte getByte(Flag flag) {
            if (flag == Flag::BinaryType) {
                return std::byte{0x20};
            } else if (flag == Flag::GeometryEmpty) {
                return std::byte{0x10};
            } else if (flag == Flag::EnvelopeIndicator) {
                return std::byte{0x0e};
            } else if (flag == Flag::Endianess) {
                return std::byte{0x01};
            } else {
                return std::byte{};
            }
        }

    }

}