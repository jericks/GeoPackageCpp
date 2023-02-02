#pragma once

#include <iostream>
#include "Bounds.hpp"

namespace geopackage {

    class TileMatrixSet {

        private:

            std::string tableName;
            int srsId;
            geopackage::Bounds bounds;
                
        public:

            TileMatrixSet(std::string tableName, int srsId, geopackage::Bounds bounds);

            std::string getTableName() const;

            int getSrsId() const;

            geopackage::Bounds getBounds() const;

    };

    std::ostream& operator << (std::ostream& os, const TileMatrixSet& tileMatrixSet);

}