#include "DataType.hpp"

namespace geopackage {

    std::string getStringFromDataType(DataType dataType) {
        if (dataType == DataType::FEATURES) {
            return "features";
        } else if (dataType == DataType::TILES) {
            return "tiles";
        } else {
            return "";
        }
    }

    DataType getDataTypeFromString(std::string str) {
        if (str == "features") {
            return DataType::FEATURES;
        } else {
            return DataType::TILES;
        }
    }

}