#include "GeometryColumn.hpp"

namespace geopackage {

    GeometryColumn::GeometryColumn(std::string tableName, std::string columnName, GeometryType geometryType, int srsId, Dimension dimension) :
        tableName(tableName), columnName(columnName), geometryType(geometryType), srsId(srsId), dimension(dimension) {}    

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

    Dimension GeometryColumn::getDimension() const {
        return dimension;
    }

    bool GeometryColumn::hasZ() const {
        return dimension::hasZ(dimension);
    }

    bool GeometryColumn::hasM() const {
        return dimension::hasM(dimension);
    }

    std::ostream& operator << (std::ostream& os, const GeometryColumn& e) {
        os << "GEOMETRYCOLUMN (tableName = " << e.getTableName() << ", columnName = " << e.getColumnName() 
            << ", geometryType = " << geometrytype::toString(e.getGeometryType())  
            << ", srsId = " << e.getSrsId()  
            << ", dimension = " << dimension::toString(e.getDimension())
            << ")";
        return os;
    }

}