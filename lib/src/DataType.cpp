#include "DataType.hpp"

namespace geopackage {

    namespace datatype {

        std::string toString(DataType dataType) {
            if (dataType == DataType::FEATURES) {
                return "features";
            } else if (dataType == DataType::TILES) {
                return "tiles";
            } else {
                return "";
            }
        }

        DataType getDataType(std::string str) {
            if (str == "features") {
                return DataType::FEATURES;
            } else {
                return DataType::TILES;
            }
        }

    }

    std::ostream& operator << (std::ostream& os, const DataType& dataType) {
        os << datatype::toString(dataType);
        return os;
    }

}