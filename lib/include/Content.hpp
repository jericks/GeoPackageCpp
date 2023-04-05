#pragma once

#include <string>
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include "Bounds.hpp"
#include "DataType.hpp"

namespace geopackage {

    class Content {

        private:

            std::string tableName;
            DataType dataType;
            std::string identifier;
            std::string description;
            std::string lastChange;
            Bounds bounds;
            int srsId;

            static std::string now();
                
        public:

            Content(std::string tableName, DataType dataType, std::string identifier, std::string description, std::string lastChange, Bounds bounds, int srsId);

            Content(std::string tableName, DataType dataType, std::string identifier, std::string description, Bounds bounds, int srsId);

            std::string getTableName() const;

            DataType getDataType() const;

            std::string getIdentifier() const;

            std::string getDescription() const;

            std::string getLastChange() const;

            Bounds getBounds() const;

            int getSrsId() const;

    };

    std::ostream& operator << (std::ostream& os, const Content& content);

}