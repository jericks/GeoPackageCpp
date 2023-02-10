#pragma once

#include <string>

namespace geopackage {

    enum class Scope {
        READ_WRITE, WRITE_ONLY
    };

    namespace scope {

        std::string toString(Scope scope);

        Scope getScope(std::string str);

    }

    std::ostream& operator << (std::ostream& os, const Scope& scope);

}