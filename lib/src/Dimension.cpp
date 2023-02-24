#include "Dimension.hpp"

namespace geopackage {

    namespace dimension {

        std::string toString(Dimension dimension) {
            if (dimension == Dimension::Two) {
                return "2D";
            } else if (dimension == Dimension::TwoMeasured) {
                return "2DM";
            } else if (dimension == Dimension::Three) {
                return "3D";
            } else if (dimension == Dimension::ThreeMeasured) {
                return "3DM";
            } else {
                return "";
            }
        }

    }

    std::ostream& operator << (std::ostream& os, const Dimension& dimension) {
        os << dimension::toString(dimension);
        return os;
    }

}