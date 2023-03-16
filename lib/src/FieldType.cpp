#include "FieldType.hpp"

namespace geopackage {

    std::ostream& operator << (std::ostream& os, const FieldType& fieldType) {
        os << fieldtype::toString(fieldType);
        return os;
    }

    namespace fieldtype {

        std::string toString(FieldType fieldType) {
            if (fieldType == FieldType::Integer) {
                return "Integer";
            } else if (fieldType == FieldType::String) {
                return "String";
            } else if (fieldType == FieldType::Double) {
                return "Double";
            } else if (fieldType == FieldType::Boolean) {
                return "Boolean";
            } else if (fieldType == FieldType::Blob) {
                return "Blob";
            } else if (fieldType == FieldType::Geometry) {
                return "Geometry";
            } else {
                return "";
            }
        }

        std::string getDatabaseType(FieldType fieldType) {
            if (fieldType == FieldType::Integer) {
                return "INTEGER";
            } else if (fieldType == FieldType::String) {
                return "TEXT";
            } else if (fieldType == FieldType::Double) {
                return "REAL";
            } else if (fieldType == FieldType::Boolean) {
                return "BOOLEAN";
            } else if (fieldType == FieldType::Blob) {
                return "BLOB";
            } else if (fieldType == FieldType::Geometry) {
                return "BLOB";
            } else {
                return "TEXT";
            }
        }

        FieldType getFieldType(std::string str) {
            if (str == "integer" || str == "INTEGER") {
                return FieldType::Integer;
            } else if (str == "geometry") {
                return FieldType::Geometry;
            } else if (str == "string" || str == "TEXT") {
                return FieldType::String;
            } else if (str == "double" || str == "REAL") {
                return FieldType::Double;
            } else if (str == "boolean" || str == "BOOLEAN") {
                return FieldType::Boolean;
            } else if (str == "blob" || str == "BLOB") {
                return FieldType::Blob;
            } else {
                return FieldType::String;
            }
        }

    }

}