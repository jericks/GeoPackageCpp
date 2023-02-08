#pragma once

#include <string>
#include <iostream>
#include "Bounds.hpp"
#include "DataType.hpp"

namespace geopackage {

    class Content {

        private:

            std::string tableName;
            std::string dataType;
            std::string identifier;
            std::string description;
            std::string lastChange;
            Bounds bounds;
            int srsId;
                
        public:

            Content(std::string tableName, std::string dataType, std::string identifier, std::string description, std::string lastChange, Bounds bounds, int srsId);

            std::string getTableName() const;

            std::string getDataType() const;

            std::string getIdentifier() const;

            std::string getDescription() const;

            std::string getLastChange() const;

            Bounds getBounds() const;

            int getSrsId() const;

    };

    std::ostream& operator << (std::ostream& os, const Content& content);

}