#pragma once

#include <string>
#include <ostream>

namespace geopackage {

    enum class Dimension {
        Two,
        TwoMeasured,
        Three,
        ThreeMeasured
    };

    namespace dimension {

        std::string toString(Dimension dimension);

        bool hasZ(Dimension dimension);

        bool hasM(Dimension dimension);

    }

    std::ostream& operator << (std::ostream& os, const Dimension& dimensione);


}