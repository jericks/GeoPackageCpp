#pragma once

#include <iostream>
#include <string>
#include "SQLiteCpp/SQLiteCpp.h"
#include "Extension.hpp"
#include "SpatialRef.hpp"
#include "TileMatrix.hpp"
#include "TileMatrixSet.hpp"

namespace geopackage {

    class GeoPackage {

        private:

            std::string fileName;

            SQLite::Database db;

            void createTables(); 

            void insertDefaultSpatialRefs();

        public:

            GeoPackage(std::string fileName);

            ~GeoPackage();

            std::string getFileName() const;
            
            void deleteTable(std::string name);

            // SpatialRef

            void addSpatialRef(const SpatialRef& s);

            void updateSpatialRef(const SpatialRef& s);

            void setSpatialRef(const SpatialRef& s);

            void deleteSpatialRef(const SpatialRef& s);

            std::optional<SpatialRef> getSpatialRef(int srsId);   

            void spatialRefs(std::function<void(SpatialRef& s)> f);

            // Content

            // Geometry Columns

            // Extension

            void addExtension(const Extension& e);

            // Tile Matrix Set

            void addTileMatrixSet(const TileMatrixSet& t);

            void updateTileMatrixSet(const TileMatrixSet& t);

            void setTileMatrixSet(const TileMatrixSet& s);

            void deleteTileMatrixSet(const TileMatrixSet& s);

            std::optional<TileMatrixSet> getTileMatrixSet(std::string name);   

            void tileMatrixSets(std::function<void(TileMatrixSet& s)> f);

            // Tile Matrix

            void addTileMatrix(const TileMatrix& t);

            void updateTileMatrix(const TileMatrix& t);

            void setTileMatrix(const TileMatrix& s);

            void deleteTileMatrix(const TileMatrix& s);

            std::optional<TileMatrix> getTileMatrix(std::string name, int zoomLevel);   

            void tileMatrices(std::string name, std::function<void(TileMatrix& s)> f);

            void tileMatrices(std::function<void(TileMatrix& s)> f);

            // Tile

            void createTileTable(std::string name);

            // Feature

    };

    std::ostream& operator << (std::ostream& os, const GeoPackage& g);

}