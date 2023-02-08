#pragma once

#include <iostream>
#include "Scope.hpp"

namespace geopackage {

    class Extension {

        private:

            std::string tableName;
            std::string columnName;
            std::string extensionName;
            std::string definition;
            Scope scope;
                
        public:

            Extension(std::string tableName, std::string columnName, std::string extensionName, std::string definition, Scope scope);

            std::string getTableName() const;

            std::string getColumnName() const;

            std::string getExtensionName() const;

            std::string getDefinition() const;

            Scope getScope() const;

    };

    std::ostream& operator << (std::ostream& os, const Extension& extension);

}