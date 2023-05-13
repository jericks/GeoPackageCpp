#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>
#include <fstream>
#include <functional>
#include <filesystem>
#include <optional>
#include "SQLiteCpp/SQLiteCpp.h"
#include "Content.hpp"
#include "DataType.hpp"
#include "Extension.hpp"
#include "Feature.hpp"
#include "GeometryColumn.hpp"
#include "GeoPackageGeometryWriter.hpp"
#include "GeoPackageGeometryReader.hpp"
#include "Schema.hpp"
#include "SpatialRef.hpp"
#include "Tile.hpp"
#include "TileMatrix.hpp"
#include "TileMatrixSet.hpp"

namespace geopackage {

    class GeoPackage {

        private:

            std::string fileName;

            SQLite::Database db;

            void createTables(); 

            std::string getPrimaryKey(std::string tableName);

            std::string getGeometryColumnName(std::string tableName);

            int bindFeatureValues(SQLite::Statement& statement, Feature feature, int startIndex);

            int bindFeatureValuesForUpdate(SQLite::Statement& statement, Feature feature, std::string primaryKey, int startIndex);

            void bindFeatureValue(SQLite::Statement& statement, std::any value, int index);

            std::vector<std::string> getColumnNames(std::string table);

            Feature getFeature(SQLite::Statement& query, GeoPackageGeometryReader& reader, std::string geometryColumnName, std::string primaryKey, std::map<std::string, FieldType> fieldMap);

            bool isImage(std::string extension);

            std::string now();

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

            void insertDefaultSpatialRefs();

            // Content

            void addContent(const Content& c);

            void updateContent(const Content& c);

            void setContent(const Content& c);

            void deleteContent(const Content& c);

            std::optional<Content> getContent(std::string tableName);   

            void contents(DataType dataType, std::function<void(Content& e)> f);

            void contents(std::function<void(Content& e)> f);

            // Geometry Columns

            void addGeometryColumn(const GeometryColumn& e);

            void updateGeometryColumn(const GeometryColumn& e);

            void setGeometryColumn(const GeometryColumn& e);

            void deleteGeometryColumn(const GeometryColumn& e);

            std::optional<GeometryColumn> getGeometryColumn(std::string tableName);   

            void geometryColumns(std::function<void(GeometryColumn& e)> f);

            // Extension

            void addExtension(const Extension& e);

            void updateExtension(const Extension& e);

            void setExtension(const Extension& e);

            void deleteExtension(const Extension& e);

            std::optional<Extension> getExtension(std::string extensionName);   

            void extensions(std::function<void(Extension& e)> f);

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

            int getMinZoom(std::string name);

            int getMaxZoom(std::string name);
            
            int countTiles(std::string name);

            int countTiles(std::string name, int zoom);

            void addTile(std::string name, const Tile& t);

            void updateTile(std::string name, const Tile& t);

            void setTile(std::string name, const Tile& t);

            void deleteTile(std::string name, const Tile& t);

            std::optional<Tile> getTile(std::string name, int z, int c, int r);    

            void tiles(std::string name, int zoom, std::function<void(Tile& t)> f);

            void createGlobalGeodeticTileLayer(std::string name, int tileSize, int maxZoomLevel);

            void createGlobalMercatorTileLayer(std::string name, int tileSize, int maxZoomLevel);

            void loadTilesFromDirectory(std::string name, std::string directory);

            void exportTilesToDirectory(std::string name, std::string format, std::string directory);

            // Feature

            void createFeatureTable(const Schema& schema);

            void createFeatureLayer(const Schema& schema, const Bounds& bounds);

            void addFeature(std::string name, const Feature& feature);

            Schema getSchema(std::string name);

            int countFeatures(std::string name);

            void updateFeature(std::string name, const Feature& f);

            void setFeature(std::string name, const Feature& f);

            void deleteFeature(std::string name, const Feature& f);

            void deleteAllFeatures(std::string name);

            std::optional<Feature> getFeature(std::string name, int id);

            void features(std::string name, std::function<void(Feature& feature)> f);

    };

    std::ostream& operator << (std::ostream& os, const GeoPackage& g);

}