#include "Extension.hpp"

namespace geopackage {

    Extension::Extension(std::string table_name, std::string column_name, std::string extension_name, std::string def, std::string sc) :
        tableName(table_name), columnName(column_name), extensionName(extension_name), definition(def), scope(sc) {}

    std::string Extension::getTableName() const {
        return tableName;
    }

    std::string Extension::getColumnName() const {
        return columnName;
    }

    std::string Extension::getExtensionName() const {
        return extensionName;
    }

    std::string Extension::getDefinition() const {
        return definition;
    }

    std::string Extension::getScope() const {
        return scope;
    }

    std::ostream& operator << (std::ostream& os, const Extension& e) {
        os << "EXTENSION (tableName = " << e.getTableName() << ", columnName = " << e.getColumnName() 
            << ", extensionName = " << e.getExtensionName()  
            << ", definition = " << e.getDefinition()  
            << ", scope = " << e.getScope()  
            << ")";
        return os;
    }

}