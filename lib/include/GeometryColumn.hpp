#pragma once

#include <iostream>
#include "GeometryType.hpp"

namespace geopackage {

    class GeometryColumn {

        private:

            std::string tableName;
            std::string columnName;
            GeometryType geometryType;
            int srsId;
            bool m;
            bool z;
                
        public:

            GeometryColumn(std::string tableName, std::string columnName, GeometryType geometryType, int srsId, bool hasM, bool hasZ);

            std::string getTableName() const;

            std::string getColumnName() const;

            GeometryType getGeometryType() const;

            int getSrsId() const;

            bool hasM() const;

            bool hasZ() const;

    };

    std::ostream& operator << (std::ostream& os, const GeometryColumn& geometryColumn);

}