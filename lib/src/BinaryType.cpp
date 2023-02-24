#include "BinaryType.hpp"

namespace geopackage {

    namespace binarytype {

        std::string toString(BinaryType binaryType) {
            if (binaryType == BinaryType::Standard) {
                return "Standard";
            } else if (binaryType == BinaryType::Extended) {
                return "Extended";
            } else {
                return "";
            }
        }

        int getValue(BinaryType binaryType) {
            if (binaryType == BinaryType::Standard) {
                return 0;
            } else if (binaryType == BinaryType::Extended) {
                return 1;
            } else {
                return -1;
            }
        }

        std::byte getByte(BinaryType binaryType) {
             if (binaryType == BinaryType::Standard) {
                return std::byte{0};
            } else if (binaryType == BinaryType::Extended) {
                return std::byte{1};
            } else {
                return std::byte{};
            }
        }

    }

    std::ostream& operator << (std::ostream& os, const BinaryType& binaryType) {
        os << binarytype::toString(binaryType);
        return os;
    }

}