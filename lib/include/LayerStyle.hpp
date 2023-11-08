#pragma once

#include <string>
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

namespace geopackage {

    class LayerStyle {

        private:

            int id;
            std::string tableCatalog;
            std::string tableSchema;
            std::string tableName;
            std::string geometryColumn;
            std::string styleName;
            std::string styleQML;
            std::string styleSLD;
            bool useAsDefault;
            std::string description;
            std::string owner;
            std::string ui;
            std::string updateTime;

            static std::string now();
                
        public:

            LayerStyle(
                int id,
                std::string tableCatalog,
                std::string tableSchema,
                std::string tableName,
                std::string geometryColumn,
                std::string styleName,
                std::string styleQML,
                std::string styleSLD,
                bool useAsDefault,
                std::string description,
                std::string owner,
                std::string ui,
                std::string updateTime
            );

            LayerStyle(
                std::string tableCatalog,
                std::string tableSchema,
                std::string tableName,
                std::string geometryColumn,
                std::string styleName,
                std::string styleQML,
                std::string styleSLD,
                bool useAsDefault,
                std::string description,
                std::string owner,
                std::string ui
            );

            int getId() const;

            std::string getTableCatalog() const;

            std::string getTableSchema() const;

            std::string getTableName() const;

            std::string getGeometryColumn() const;

            std::string getStyleName() const;

            std::string getStyleQML() const;

            std::string getStyleSLD() const;

            bool getUseAsDefault() const;

            std::string getDescription() const;

            std::string getOwner() const;

            std::string getUi() const;

            std::string getUpdateTime() const;

    };

    std::ostream& operator << (std::ostream& os, const LayerStyle& layerStyle);

}