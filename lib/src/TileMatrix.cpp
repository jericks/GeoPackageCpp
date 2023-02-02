#include "TileMatrix.hpp"

namespace geopackage {

    TileMatrix::TileMatrix(std::string table_name, int zoom_level, Size<int> matrix_size, Size<int> tile_size, Size<double> pixel_size) :
        tableName(table_name), zoomLevel(zoom_level), matrixSize(matrix_size), tileSize(tile_size), pixelSize(pixel_size) {}

    std::string TileMatrix::getTableName() const {
        return tableName;
    }

    int TileMatrix::getZoomLevel() const {
        return zoomLevel;
    }

    Size<int> TileMatrix::getMatrixSize() const {
        return matrixSize;
    }

    Size<int> TileMatrix::getTileSize() const {
        return tileSize;
    }

    Size<double> TileMatrix::getPixelSize() const {
        return pixelSize;
    }

    std::ostream& operator << (std::ostream& os, const TileMatrix& s) {
        os << "TILE_MATRIX (tableName = " << s.getTableName() << ", zoomLevel = " << s.getZoomLevel() 
            << ", matrixSize = " << s.getMatrixSize()  
            << ", tileSize = " << s.getTileSize()  
            << ", pixelSize = " << s.getPixelSize()  
            << ")";
        return os;
    }

}