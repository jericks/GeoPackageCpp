#include "Scope.hpp"

namespace geopackage {

    namespace scope {

        std::string toString(Scope scope) {
            if (scope == Scope::READ_WRITE) {
                return "read-write";
            } else if (scope == Scope::WRITE_ONLY) {
                return "write-only";
            } else {
                return "";
            }
        }

        Scope getScope(std::string str) {
            if (str == "read-write") {
                return Scope::READ_WRITE;
            } else {
                return Scope::WRITE_ONLY;
            }
        }

    }

}