#pragma once

#include <iostream>
#include "GeometryType.hpp"
#include "Dimension.hpp"

namespace geopackage {

    class GeometryColumn {

        private:

            std::string tableName;
            std::string columnName;
            GeometryType geometryType;
            int srsId;
            Dimension dimension;
                
        public:

            GeometryColumn(std::string tableName, std::string columnName, GeometryType geometryType, int srsId, Dimension dimension);

            std::string getTableName() const;

            std::string getColumnName() const;

            GeometryType getGeometryType() const;

            Dimension getDimension() const;

            int getSrsId() const;

            bool hasZ() const;

            bool hasM() const;

    };

    std::ostream& operator << (std::ostream& os, const GeometryColumn& geometryColumn);

}