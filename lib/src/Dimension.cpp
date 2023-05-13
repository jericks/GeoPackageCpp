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

        bool hasZ(Dimension dimension) {
            return dimension == Dimension::Three || dimension == Dimension::ThreeMeasured;
        }

        bool hasM(Dimension dimension) {
            return dimension == Dimension::TwoMeasured || dimension == Dimension::ThreeMeasured;
        }

        Dimension getDimension(bool hasZ, bool hasM) {
            if (hasZ && hasM) {
                return Dimension::ThreeMeasured;
            } else if (hasZ) {
                return Dimension::Three;
            } else if (hasM) {
                return Dimension::TwoMeasured;
            } else {
                return Dimension::Two;
            }
        }

    }

    std::ostream& operator << (std::ostream& os, const Dimension& dimension) {
        os << dimension::toString(dimension);
        return os;
    }

}