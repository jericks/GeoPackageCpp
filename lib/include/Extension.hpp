#pragma once

#include <iostream>

namespace geopackage {

    class Extension {

        private:

            std::string tableName;
            std::string columnName;
            std::string extensionName;
            std::string definition;
            std::string scope;
                
        public:

            Extension(std::string tableName, std::string columnName, std::string extensionName, std::string definition, std::string scope);

            std::string getTableName() const;

            std::string getColumnName() const;

            std::string getExtensionName() const;

            std::string getDefinition() const;

            std::string getScope() const;

    };

    std::ostream& operator << (std::ostream& os, const Extension& extension);

}