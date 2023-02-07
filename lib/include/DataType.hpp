#pragma once

#include <string>

namespace geopackage {

    enum class DataType {
        FEATURES, TILES
    };

    std::string getStringFromDataType(DataType dataType);

    DataType getDataTypeFromString (std::string str);

}