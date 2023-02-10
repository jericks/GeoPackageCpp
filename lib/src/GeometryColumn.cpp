#include "GeometryColumn.hpp"

namespace geopackage {

    GeometryColumn::GeometryColumn(std::string tableName, std::string columnName, GeometryType geometryType, int srsId, bool hasZ, bool hasM) :
        tableName(tableName), columnName(columnName), geometryType(geometryType), srsId(srsId), z(hasZ), m(hasM) {}

    std::string GeometryColumn::getTableName() const {
        return tableName;
    }

    std::string GeometryColumn::getColumnName() const {
        return columnName;
    }

    GeometryType GeometryColumn::getGeometryType() const {
        return geometryType;
    }

    int GeometryColumn::getSrsId() const {
        return srsId;
    }

    bool GeometryColumn::hasZ() const {
        return z;
    }

    bool GeometryColumn::hasM() const {
        return m;
    }

    std::ostream& operator << (std::ostream& os, const GeometryColumn& e) {
        os << "GEOMETRYCOLUMN (tableName = " << e.getTableName() << ", columnName = " << e.getColumnName() 
            << ", geometryType = " << geometrytype::toString(e.getGeometryType())  
            << ", srsId = " << e.getSrsId()  
            << ", hasZ = " << e.hasZ()
            << ", hasM = " << e.hasM()
            << ")";
        return os;
    }

}