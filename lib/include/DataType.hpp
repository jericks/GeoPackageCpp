#pragma once

#include <string>

namespace geopackage {

    enum class DataType {
        FEATURES, TILES
    };

    namespace datatype {

        std::string toString(DataType dataType);

        DataType getDataType(std::string str);

    }

}