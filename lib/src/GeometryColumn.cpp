#include "GeometryColumn.hpp"

namespace geopackage {

    GeometryColumn::GeometryColumn(std::string tableName, std::string columnName, GeometryType geometryType, int srsId, bool hasM, bool hasZ) :
        tableName(tableName), columnName(columnName), geometryType(geometryType), srsId(srsId), m(hasM), z(hasZ) {}

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

    bool GeometryColumn::hasM() const {
        return m;
    }

    bool GeometryColumn::hasZ() const {
        return z;
    }

    std::ostream& operator << (std::ostream& os, const GeometryColumn& e) {
        os << "GEOMETRYCOLUMN (tableName = " << e.getTableName() << ", columnName = " << e.getColumnName() 
            << ", geometryType = " << geometrytype::toString(e.getGeometryType())  
            << ", srsId = " << e.getSrsId()  
            << ", hasM = " << e.hasM()
            << ", hasZ = " << e.hasZ()
            << ")";
        return os;
    }

}