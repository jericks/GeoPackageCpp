#include "FieldType.hpp"

namespace geopackage {

    std::ostream& operator << (std::ostream& os, const FieldType& fieldType) {
        os << fieldtype::toString(fieldType);
        return os;
    }

    namespace fieldtype {

        std::string toString(FieldType fieldType) {
            if (fieldType == FieldType::Integer) {
                return "integer";
            } else if (fieldType == FieldType::String) {
                return "string";
            } else if (fieldType == FieldType::Double) {
                return "double";
            } else if (fieldType == FieldType::Boolean) {
                return "boolean";
            } else if (fieldType == FieldType::Blob) {
                return "blob";
            } else if (fieldType == FieldType::Geometry) {
                return "geometry";
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
            if (str == "integer") {
                return FieldType::Integer;
            } else if (str == "geometry") {
                return FieldType::Geometry;
            } else if (str == "string") {
                return FieldType::String;
            } else if (str == "double") {
                return FieldType::Double;
            } else if (str == "boolean") {
                return FieldType::Boolean;
            } else if (str == "blob") {
                return FieldType::Blob;
            } else {
                return FieldType::String;
            }
        }

    }

}