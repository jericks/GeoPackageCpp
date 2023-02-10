#pragma once

#include <iostream>

namespace geopackage {

    enum class FieldType {
        String, Integer, Double, Boolean, Blob, Geometry
    };

    namespace fieldtype {

        std::string toString(FieldType fieldType);

        std::string getDatabaseType(FieldType fieldType);

        FieldType getFieldType(std::string str);

    }

    std::ostream& operator << (std::ostream& os, const FieldType& fieldType);

}