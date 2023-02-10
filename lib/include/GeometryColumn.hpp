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
            bool z;
            bool m;
                
        public:

            GeometryColumn(std::string tableName, std::string columnName, GeometryType geometryType, int srsId, bool hasZ, bool hasM);

            std::string getTableName() const;

            std::string getColumnName() const;

            GeometryType getGeometryType() const;

            int getSrsId() const;

            bool hasZ() const;

            bool hasM() const;

    };

    std::ostream& operator << (std::ostream& os, const GeometryColumn& geometryColumn);

}