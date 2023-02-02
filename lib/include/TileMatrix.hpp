#pragma once

#include <iostream>
#include "Size.hpp"

namespace geopackage {

    class TileMatrix {

        private:

            std::string tableName;
            int zoomLevel;
            Size<int> matrixSize;
            Size<int> tileSize;
            Size<double> pixelSize;
                
        public:

            TileMatrix(std::string tableName, int zoomLevel, Size<int> matrixSize, Size<int> tileSize, Size<double> pixelSize);

            std::string getTableName() const;

            int getZoomLevel() const;

            Size<int> getMatrixSize() const;

            Size<int> getTileSize() const;

            Size<double> getPixelSize() const;

    };

    std::ostream& operator << (std::ostream& os, const TileMatrix& tileMatrix);

}