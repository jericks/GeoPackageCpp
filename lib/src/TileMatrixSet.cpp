#include "TileMatrixSet.hpp"

namespace geopackage {

    TileMatrixSet::TileMatrixSet(std::string table_name, int srs_id, geopackage::Bounds b) :
        tableName(table_name), srsId(srs_id), bounds(b) {}

    std::string TileMatrixSet::getTableName() const {
        return tableName;
    }

    int TileMatrixSet::getSrsId() const {
        return srsId;
    }

    geopackage::Bounds TileMatrixSet::getBounds() const {
        return bounds;
    }

    std::ostream& operator << (std::ostream& os, const TileMatrixSet& s) {
        os << "TILE_MATRIX_SET (tableName = " << s.getTableName() << ", srsId = " << s.getSrsId() << ", bounds = " << s.getBounds() << ")";
        return os;
    }

}