#include <sstream>
#include <iostream>
#include <algorithm>
#include <filesystem>
#include "gtest/gtest.h"
#include "GeoPackage.hpp"

// GeoPackage

TEST(GeoPackageLibTests, GeoPackage_Create) {
    const std::string fileName = "tiles.gpkg";
    geopackage::GeoPackage gpkg { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));
    EXPECT_TRUE(std::filesystem::remove(fileName));
}

// SpatialRef

TEST(GeoPackageLibTests, SpatialRef_ToString) {
    geopackage::SpatialRef s{"WGS84", 4326, "EPSG", 4326, "GEOGCS[]", "longitude/latitude coordinates in decimal degrees on the WGS 84 spheroid"};
    std::stringstream str;
    str << s;
    EXPECT_EQ("SPATIAL_REF (srsName = WGS84, srsId = 4326)", str.str());
}

TEST(GeoPackageLibTests, GeoPackage_Add_SpatialRef) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage gpkg { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    gpkg.addSpatialRef(geopackage::SpatialRef{"WGS84", 4326, "EPSG", 4326, "GEOGCS[]", "longitude/latitude coordinates in decimal degrees on the WGS 84 spheroid"});
    std::optional<geopackage::SpatialRef> m = gpkg.getSpatialRef(4326);
    EXPECT_TRUE(m.has_value());

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_Update_SpatialRef) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage geopackage { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    geopackage.addSpatialRef(geopackage::SpatialRef{"WGS84", 4326, "EPSG", 4326, "GEOGCS[]", "longitude/latitude coordinates in decimal degrees on the WGS 84 spheroid"});
    std::optional<geopackage::SpatialRef> s1 = geopackage.getSpatialRef(4326);
    EXPECT_TRUE(s1.has_value());
    EXPECT_EQ("WGS84", s1.value().getSrsName());

    geopackage.updateSpatialRef(geopackage::SpatialRef{"EPSG:4326", 4326, "EPSG", 4326, "GEOGCS[]", "longitude/latitude coordinates in decimal degrees on the WGS 84 spheroid"});
    std::optional<geopackage::SpatialRef> s2 = geopackage.getSpatialRef(4326);
    EXPECT_TRUE(s2.has_value());
    EXPECT_EQ("EPSG:4326", s2.value().getSrsName());

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_Set_SpatialRef) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage geopackage { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    geopackage.setSpatialRef(geopackage::SpatialRef{"WGS84", 4326, "EPSG", 4326, "GEOGCS[]", "longitude/latitude coordinates in decimal degrees on the WGS 84 spheroid"});
    std::optional<geopackage::SpatialRef> s1 = geopackage.getSpatialRef(4326);
    EXPECT_TRUE(s1.has_value());
    EXPECT_EQ("WGS84", s1.value().getSrsName());

    geopackage.setSpatialRef(geopackage::SpatialRef{"EPSG:4326", 4326, "EPSG", 4326, "GEOGCS[]", "longitude/latitude coordinates in decimal degrees on the WGS 84 spheroid"});
    std::optional<geopackage::SpatialRef> s2 = geopackage.getSpatialRef(4326);
    EXPECT_TRUE(s2.has_value());
    EXPECT_EQ("EPSG:4326", s2.value().getSrsName());

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_Delete_SpatialRef) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage geopackage { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    geopackage.addSpatialRef(geopackage::SpatialRef{"WGS84", 4326, "EPSG", 4326, "GEOGCS[]", "longitude/latitude coordinates in decimal degrees on the WGS 84 spheroid"});
    std::optional<geopackage::SpatialRef> s1 = geopackage.getSpatialRef(4326);
    EXPECT_TRUE(s1.has_value());
    EXPECT_EQ("WGS84", s1.value().getSrsName());

    geopackage.deleteSpatialRef(s1.value());
    std::optional<geopackage::SpatialRef> s2 = geopackage.getSpatialRef(4326);
    EXPECT_FALSE(s2.has_value());

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_Get_SpatialRef) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage geopackage { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    std::optional<geopackage::SpatialRef> s1 = geopackage.getSpatialRef(4326);
    EXPECT_FALSE(s1.has_value());
    geopackage.addSpatialRef(geopackage::SpatialRef{"WGS84", 4326, "EPSG", 4326, "GEOGCS[]", "longitude/latitude coordinates in decimal degrees on the WGS 84 spheroid"});
    std::optional<geopackage::SpatialRef> s2 = geopackage.getSpatialRef(4326);
    EXPECT_TRUE(s2.has_value());

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_SpatialRefs) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage geopackage { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    geopackage.addSpatialRef(geopackage::SpatialRef{"WGS84", 4326, "EPSG", 4326, "GEOGCS[]", "longitude/latitude coordinates in decimal degrees on the WGS 84 spheroid"});
    geopackage.addSpatialRef(geopackage::SpatialRef{"EPSG:2927", 2927, "EPSG", 2927, "PROJ[]", "wa state plane south"});
    
    int counter = 0;    
    geopackage.spatialRefs([&](geopackage::SpatialRef& s) {
        counter++;
    });
    EXPECT_EQ(2, counter);


    EXPECT_TRUE(std::filesystem::remove(fileName));
}

// TileMatrixSet

TEST(GeoPackageLibTests, TileMatrixSet_ToString) {
    geopackage::TileMatrixSet tileMatrixSet{"basemap", 4326, geopackage::Bounds{-180,-90,180,90}};
    std::stringstream str;
    str << tileMatrixSet;
    EXPECT_EQ("TILE_MATRIX_SET (tableName = basemap, srsId = 4326, bounds = BOUNDS (-180, -90, 180, 90))", str.str());
}

TEST(GeoPackageLibTests, GeoPackage_Add_TileMatrixSet) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage gpkg { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    gpkg.addTileMatrixSet(geopackage::TileMatrixSet{"basemap", 4326, geopackage::Bounds{-180,-90,180,90}});
    std::optional<geopackage::TileMatrixSet> tileMatrixSet = gpkg.getTileMatrixSet("basemap");
    EXPECT_TRUE(tileMatrixSet.has_value());

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_Update_TileMatrixSet) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage geopackage { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    geopackage.addTileMatrixSet(geopackage::TileMatrixSet{"basemap", 4326, geopackage::Bounds{-180,-90,180,90}});
    std::optional<geopackage::TileMatrixSet> s1 = geopackage.getTileMatrixSet("basemap");
    EXPECT_TRUE(s1.has_value());
    EXPECT_EQ(4326, s1.value().getSrsId());

    geopackage.updateTileMatrixSet(geopackage::TileMatrixSet{"basemap", 3857, geopackage::Bounds{-180,-85,180,85}});
    std::optional<geopackage::TileMatrixSet> s2 = geopackage.getTileMatrixSet("basemap");
    EXPECT_TRUE(s2.has_value());
    EXPECT_EQ(3857, s2.value().getSrsId());

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_Set_TileMatrixSet) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage geopackage { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    geopackage.setTileMatrixSet(geopackage::TileMatrixSet{"basemap", 4326, geopackage::Bounds{-180,-90,180,90}});
    std::optional<geopackage::TileMatrixSet> s1 = geopackage.getTileMatrixSet("basemap");
    EXPECT_TRUE(s1.has_value());
    EXPECT_EQ(4326, s1.value().getSrsId());

    geopackage.setTileMatrixSet(geopackage::TileMatrixSet{"basemap", 3857, geopackage::Bounds{-180,-85,180,85}});
    std::optional<geopackage::TileMatrixSet> s2 = geopackage.getTileMatrixSet("basemap");
    EXPECT_TRUE(s2.has_value());
    EXPECT_EQ(3857, s2.value().getSrsId());

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_Delete_TileMatrixSet) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage geopackage { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    geopackage.addTileMatrixSet(geopackage::TileMatrixSet{"basemap", 4326, geopackage::Bounds{-180,-90,180,90}});
    std::optional<geopackage::TileMatrixSet> s1 = geopackage.getTileMatrixSet("basemap");
    EXPECT_TRUE(s1.has_value());
    EXPECT_EQ(4326, s1.value().getSrsId());

    geopackage.deleteTileMatrixSet(s1.value());
    std::optional<geopackage::TileMatrixSet> s2 = geopackage.getTileMatrixSet("basemap");
    EXPECT_FALSE(s2.has_value());

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_Get_TileMatrixSet) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage geopackage { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    std::optional<geopackage::TileMatrixSet> s1 = geopackage.getTileMatrixSet("basemap");
    EXPECT_FALSE(s1.has_value());
    geopackage.addTileMatrixSet(geopackage::TileMatrixSet{"basemap", 4326, geopackage::Bounds{-180,-90,180,90}});
    std::optional<geopackage::TileMatrixSet> s2 = geopackage.getTileMatrixSet("basemap");
    EXPECT_TRUE(s2.has_value());

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_TileMatrixSets) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage geopackage { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    geopackage.addTileMatrixSet(geopackage::TileMatrixSet{"basemap", 4326, geopackage::Bounds{-180,-90,180,90}});
    geopackage.addTileMatrixSet(geopackage::TileMatrixSet{"mercator", 3857, geopackage::Bounds{-180,-85,180,85}});
    
    int counter = 0;    
    geopackage.tileMatrixSets([&](geopackage::TileMatrixSet& s) {
        counter++;
    });
    EXPECT_EQ(2, counter);


    EXPECT_TRUE(std::filesystem::remove(fileName));
}

// Tile Matrix

TEST(GeoPackageLibTests, TileMatrix_ToString) {
    geopackage::TileMatrix tileMatrix{"basemap", 0, geopackage::Size<int>{1, 1}, geopackage::Size<int>{256, 256}, geopackage::Size<double>{2.0, 2.0}};
    std::stringstream str;
    str << tileMatrix;
    EXPECT_EQ("TILE_MATRIX (tableName = basemap, zoomLevel = 0, matrixSize = SIZE (1, 1), tileSize = SIZE (256, 256), pixelSize = SIZE (2, 2))", str.str());
}

TEST(GeoPackageLibTests, GeoPackage_Add_TileMatrix) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage gpkg { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    gpkg.addTileMatrix(geopackage::TileMatrix{"basemap", 0, geopackage::Size<int>{1, 1}, geopackage::Size<int>{256, 256}, geopackage::Size<double>{2.0, 2.0}});
    std::optional<geopackage::TileMatrix> m = gpkg.getTileMatrix("basemap", 0);
    EXPECT_TRUE(m.has_value());

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_Update_TileMatrix) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage geopackage { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    geopackage.addTileMatrix(geopackage::TileMatrix{"basemap", 0, geopackage::Size<int>{1, 1}, geopackage::Size<int>{256, 256}, geopackage::Size<double>{2.0, 2.0}});
    std::optional<geopackage::TileMatrix> s1 = geopackage.getTileMatrix("basemap", 0);
    EXPECT_TRUE(s1.has_value());
    EXPECT_EQ(1, s1.value().getMatrixSize().getWidth());

    geopackage.updateTileMatrix(geopackage::TileMatrix{"basemap", 0, geopackage::Size<int>{2, 2}, geopackage::Size<int>{256, 256}, geopackage::Size<double>{2.0, 2.0}});
    std::optional<geopackage::TileMatrix> s2 = geopackage.getTileMatrix("basemap", 0);
    EXPECT_TRUE(s2.has_value());
    EXPECT_EQ(2, s2.value().getMatrixSize().getWidth());

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_Set_TileMatrix) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage geopackage { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    geopackage.setTileMatrix(geopackage::TileMatrix{"basemap", 0, geopackage::Size<int>{1, 1}, geopackage::Size<int>{256, 256}, geopackage::Size<double>{2.0, 2.0}});
    std::optional<geopackage::TileMatrix> s1 = geopackage.getTileMatrix("basemap", 0);
    EXPECT_TRUE(s1.has_value());
    EXPECT_EQ(1, s1.value().getMatrixSize().getWidth());

    geopackage.setTileMatrix(geopackage::TileMatrix{"basemap", 0, geopackage::Size<int>{2, 2}, geopackage::Size<int>{256, 256}, geopackage::Size<double>{2.0, 2.0}});
    std::optional<geopackage::TileMatrix> s2 = geopackage.getTileMatrix("basemap", 0);
    EXPECT_TRUE(s2.has_value());
    EXPECT_EQ(2, s2.value().getMatrixSize().getWidth());

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_Delete_TileMatrix) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage geopackage { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    geopackage.addTileMatrix(geopackage::TileMatrix{"basemap", 0, geopackage::Size<int>{2, 2}, geopackage::Size<int>{256, 256}, geopackage::Size<double>{2.0, 2.0}});
    std::optional<geopackage::TileMatrix> s1 = geopackage.getTileMatrix("basemap", 0);
    EXPECT_TRUE(s1.has_value());
    EXPECT_EQ(2, s1.value().getMatrixSize().getWidth());

    geopackage.deleteTileMatrix(s1.value());
    std::optional<geopackage::TileMatrix> s2 = geopackage.getTileMatrix("basemap", 0);
    EXPECT_FALSE(s2.has_value());

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_Get_TileMatrix) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage geopackage { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    std::optional<geopackage::TileMatrix> s1 = geopackage.getTileMatrix("basemap", 0);
    EXPECT_FALSE(s1.has_value());
    geopackage.addTileMatrix(geopackage::TileMatrix{"basemap", 0, geopackage::Size<int>{2, 2}, geopackage::Size<int>{256, 256}, geopackage::Size<double>{2.0, 2.0}});
    std::optional<geopackage::TileMatrix> s2 = geopackage.getTileMatrix("basemap", 0);
    EXPECT_TRUE(s2.has_value());

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_All_TileMatrices) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage geopackage { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    geopackage.addTileMatrix(geopackage::TileMatrix{"basemap", 0, geopackage::Size<int>{2, 2}, geopackage::Size<int>{256, 256}, geopackage::Size<double>{2.0, 2.0}});
    geopackage.addTileMatrix(geopackage::TileMatrix{"basemap", 1, geopackage::Size<int>{4, 4}, geopackage::Size<int>{256, 256}, geopackage::Size<double>{1.0, 1.0}});
    geopackage.addTileMatrix(geopackage::TileMatrix{"basemap", 2, geopackage::Size<int>{8, 8}, geopackage::Size<int>{256, 256}, geopackage::Size<double>{0.5, 0.5}});
    
    int counter = 0;    
    geopackage.tileMatrices([&](geopackage::TileMatrix& s) {
        counter++;
    });
    EXPECT_EQ(3, counter);


    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_TileMatrices_Layer) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage geopackage { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    geopackage.addTileMatrix(geopackage::TileMatrix{"basemap", 0, geopackage::Size<int>{2, 2}, geopackage::Size<int>{256, 256}, geopackage::Size<double>{2.0, 2.0}});
    geopackage.addTileMatrix(geopackage::TileMatrix{"basemap", 1, geopackage::Size<int>{4, 4}, geopackage::Size<int>{256, 256}, geopackage::Size<double>{1.0, 1.0}});
    geopackage.addTileMatrix(geopackage::TileMatrix{"basemap", 2, geopackage::Size<int>{8, 8}, geopackage::Size<int>{256, 256}, geopackage::Size<double>{0.5, 0.5}});

    geopackage.addTileMatrix(geopackage::TileMatrix{"tiles", 0, geopackage::Size<int>{2, 2}, geopackage::Size<int>{256, 256}, geopackage::Size<double>{2.0, 2.0}});
    geopackage.addTileMatrix(geopackage::TileMatrix{"tiles", 1, geopackage::Size<int>{4, 4}, geopackage::Size<int>{256, 256}, geopackage::Size<double>{1.0, 1.0}});
    geopackage.addTileMatrix(geopackage::TileMatrix{"tiles", 2, geopackage::Size<int>{8, 8}, geopackage::Size<int>{256, 256}, geopackage::Size<double>{0.5, 0.5}});
    
    int counter = 0;    
    geopackage.tileMatrices("tiles", [&](geopackage::TileMatrix& s) {
        counter++;
    });
    EXPECT_EQ(3, counter);


    EXPECT_TRUE(std::filesystem::remove(fileName));
}

// Extension

TEST(GeoPackageLibTests, Extension_ToString) {
    geopackage::Extension extension{"basemap", "index", "Spatial Index", "R-TREE", geopackage::Scope::READ_WRITE};
    std::stringstream str;
    str << extension;
    EXPECT_EQ("EXTENSION (tableName = basemap, columnName = index, extensionName = Spatial Index, definition = R-TREE, scope = read-write)", str.str());
}

TEST(GeoPackageLibTests, GeoPackage_Add_Extension) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage gpkg { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    gpkg.addExtension(geopackage::Extension{"basemap", "index", "Spatial Index", "R-TREE", geopackage::Scope::READ_WRITE});
    std::optional<geopackage::Extension> m = gpkg.getExtension("Spatial Index");
    EXPECT_TRUE(m.has_value());

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_Update_Extension) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage geopackage { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    geopackage.addExtension(geopackage::Extension{"basemap", "index", "Spatial Index", "R-TREE", geopackage::Scope::READ_WRITE});
    std::optional<geopackage::Extension> e = geopackage.getExtension("Spatial Index");
    EXPECT_TRUE(e.has_value());
    EXPECT_EQ("basemap", e.value().getTableName());

    geopackage.updateExtension(geopackage::Extension{"cities", "geom", "Spatial Index", "R-TREE", geopackage::Scope::READ_WRITE});
    std::optional<geopackage::Extension> e2 = geopackage.getExtension("Spatial Index");
    EXPECT_TRUE(e2.has_value());
    EXPECT_EQ("cities", e2.value().getTableName());

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_Set_Extension) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage geopackage { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    geopackage.setExtension(geopackage::Extension{"basemap", "index", "Spatial Index", "R-TREE", geopackage::Scope::READ_WRITE});
    std::optional<geopackage::Extension> e = geopackage.getExtension("Spatial Index");
    EXPECT_TRUE(e.has_value());
    EXPECT_EQ("basemap", e.value().getTableName());

    geopackage.setExtension(geopackage::Extension{"cities", "geom", "Spatial Index", "R-TREE", geopackage::Scope::READ_WRITE});
    std::optional<geopackage::Extension> e2 = geopackage.getExtension("Spatial Index");
    EXPECT_TRUE(e2.has_value());
    EXPECT_EQ("cities", e2.value().getTableName());

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_Delete_Extension) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage geopackage { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    geopackage.addExtension(geopackage::Extension{"basemap", "index", "Spatial Index", "R-TREE", geopackage::Scope::READ_WRITE});
    std::optional<geopackage::Extension> e1 = geopackage.getExtension("Spatial Index");
    EXPECT_TRUE(e1.has_value());
    EXPECT_EQ("basemap", e1.value().getTableName());

    geopackage.deleteExtension(e1.value());
    std::optional<geopackage::Extension> e2 = geopackage.getExtension("Spatial Index");
    EXPECT_FALSE(e2.has_value());

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_Get_Extension) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage geopackage { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    std::optional<geopackage::Extension> e1 = geopackage.getExtension("Spatial Index");
    EXPECT_FALSE(e1.has_value());
    geopackage.addExtension(geopackage::Extension{"basemap", "index", "Spatial Index", "R-TREE", geopackage::Scope::READ_WRITE});
    std::optional<geopackage::Extension> e2 = geopackage.getExtension("Spatial Index");
    EXPECT_TRUE(e2.has_value());

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_Get_Extension_Table) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage geopackage { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    std::optional<geopackage::Extension> e1 = geopackage.getExtension("basemap", "Spatial Index");
    EXPECT_FALSE(e1.has_value());
    geopackage.addExtension(geopackage::Extension{"basemap", "index", "Spatial Index", "R-TREE", geopackage::Scope::READ_WRITE});
    std::optional<geopackage::Extension> e2 = geopackage.getExtension("basemap", "Spatial Index");
    EXPECT_TRUE(e2.has_value());

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_Extensions) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage geopackage { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    geopackage.addExtension(geopackage::Extension{"cities", "index", "Point Index", "R-TREE", geopackage::Scope::READ_WRITE});
    geopackage.addExtension(geopackage::Extension{"rivers", "index", "Line Index", "R-TREE", geopackage::Scope::READ_WRITE});
    geopackage.addExtension(geopackage::Extension{"basemap", "index", "Polygon Index", "R-TREE", geopackage::Scope::WRITE_ONLY});
    
    int counter = 0;    
    geopackage.extensions([&](geopackage::Extension& e) {
        counter++;
    });
    EXPECT_EQ(3, counter);


    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_Extensions_Table_Name) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage geopackage { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    geopackage.addExtension(geopackage::Extension{"cities", "spatial_index", "Point Index", "R-TREE", geopackage::Scope::READ_WRITE});
    geopackage.addExtension(geopackage::Extension{"cities", "tabular_index", "Line Index", "R-TREE", geopackage::Scope::READ_WRITE});
    geopackage.addExtension(geopackage::Extension{"basemap", "index", "Polygon Index", "R-TREE", geopackage::Scope::WRITE_ONLY});
    
    int counter = 0;    
    geopackage.extensionsByTable("cities", [&](geopackage::Extension& e) {
        counter++;
    });
    EXPECT_EQ(2, counter);

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_Extensions_Name) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage geopackage { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    geopackage.addExtension(geopackage::Extension{"cities", "geom", "metadata", "Metadata", geopackage::Scope::READ_WRITE});
    geopackage.addExtension(geopackage::Extension{"cities", "geom", "attributes", "Attribute Index", geopackage::Scope::READ_WRITE});
    geopackage.addExtension(geopackage::Extension{"basemap", "geom", "index", "R-TREE", geopackage::Scope::WRITE_ONLY});
    
    int counter = 0;    
    geopackage.extensionsByName("index", [&](geopackage::Extension& e) {
        counter++;
    });
    EXPECT_EQ(1, counter);

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

// Geometry Column

TEST(GeoPackageLibTests, GeometryColumn_ToString) {
    geopackage::GeometryColumn geometryColumn {"cities", "the_geom", geopackage::GeometryType::POINT, 4326, geopackage::Dimension::Three};
    std::stringstream str;
    str << geometryColumn;
    EXPECT_EQ("GEOMETRYCOLUMN (tableName = cities, columnName = the_geom, geometryType = Point, srsId = 4326, dimension = 3D)", str.str());
}

TEST(GeoPackageLibTests, GeoPackage_Add_GeometryColumn) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage gpkg { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    gpkg.addGeometryColumn(geopackage::GeometryColumn{"cities", "the_geom", geopackage::GeometryType::POINT, 4326, geopackage::Dimension::Three});
    std::optional<geopackage::GeometryColumn> gc = gpkg.getGeometryColumn("cities");
    EXPECT_TRUE(gc.has_value());

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_Update_GeometryColumn) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage geopackage { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    geopackage.addGeometryColumn(geopackage::GeometryColumn{"cities", "the_geom", geopackage::GeometryType::POINT, 4326, geopackage::Dimension::Three});
    std::optional<geopackage::GeometryColumn> gc = geopackage.getGeometryColumn("cities");
    EXPECT_TRUE(gc.has_value());
    EXPECT_EQ("cities", gc.value().getTableName());
    EXPECT_EQ(1, gc.value().hasZ());
    EXPECT_EQ(0, gc.value().hasM());

    geopackage.updateGeometryColumn(geopackage::GeometryColumn{"cities", "the_geom", geopackage::GeometryType::POINT, 2927, geopackage::Dimension::TwoMeasured});
    std::optional<geopackage::GeometryColumn> gc2 = geopackage.getGeometryColumn("cities");
    EXPECT_TRUE(gc2.has_value());
    EXPECT_EQ("cities", gc2.value().getTableName());
    EXPECT_EQ(0, gc2.value().hasZ());
    EXPECT_EQ(1, gc2.value().hasM());

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_Set_GeometryColumn) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage geopackage { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    geopackage.setGeometryColumn(geopackage::GeometryColumn{"cities", "the_geom", geopackage::GeometryType::POINT, 4326, geopackage::Dimension::Three});
    std::optional<geopackage::GeometryColumn> gc = geopackage.getGeometryColumn("cities");
    EXPECT_TRUE(gc.has_value());
    EXPECT_EQ("cities", gc.value().getTableName());
    EXPECT_EQ(1, gc.value().hasZ());
    EXPECT_EQ(0, gc.value().hasM());

    geopackage.setGeometryColumn(geopackage::GeometryColumn{"cities", "the_geom", geopackage::GeometryType::POINT, 2927, geopackage::Dimension::TwoMeasured});
    std::optional<geopackage::GeometryColumn> gc2 = geopackage.getGeometryColumn("cities");
    EXPECT_TRUE(gc2.has_value());
    EXPECT_EQ("cities", gc2.value().getTableName());
    EXPECT_EQ(0, gc2.value().hasZ());
    EXPECT_EQ(1, gc2.value().hasM());

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_Delete_GeometryColumn) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage geopackage { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    geopackage.addGeometryColumn(geopackage::GeometryColumn{"cities", "the_geom", geopackage::GeometryType::POINT, 4326, geopackage::Dimension::Three});
    std::optional<geopackage::GeometryColumn> e1 = geopackage.getGeometryColumn("cities");
    EXPECT_TRUE(e1.has_value());
    EXPECT_EQ("cities", e1.value().getTableName());

    geopackage.deleteGeometryColumn(e1.value());
    std::optional<geopackage::GeometryColumn> e2 = geopackage.getGeometryColumn("cities");
    EXPECT_FALSE(e2.has_value());

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_Get_GeometryColumn) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage geopackage { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    std::optional<geopackage::GeometryColumn> e1 = geopackage.getGeometryColumn("cities");
    EXPECT_FALSE(e1.has_value());
    geopackage.addGeometryColumn(geopackage::GeometryColumn{"cities", "the_geom", geopackage::GeometryType::POINT, 4326, geopackage::Dimension::Three});
    std::optional<geopackage::GeometryColumn> e2 = geopackage.getGeometryColumn("cities");
    EXPECT_TRUE(e2.has_value());

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_GeometryColumns) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage geopackage { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    geopackage.addGeometryColumn(geopackage::GeometryColumn{"cities", "the_geom", geopackage::GeometryType::POINT, 4326, geopackage::Dimension::Two});
    geopackage.addGeometryColumn(geopackage::GeometryColumn{"rivers", "the_geom", geopackage::GeometryType::LINESTRING, 4326, geopackage::Dimension::Three});
    geopackage.addGeometryColumn(geopackage::GeometryColumn{"parcels", "the_geom", geopackage::GeometryType::MULTIPOLYGON, 4326, geopackage::Dimension::Two});
    
    int counter = 0;    
    geopackage.geometryColumns([&](geopackage::GeometryColumn& e) {
        counter++;
    });
    EXPECT_EQ(3, counter);


    EXPECT_TRUE(std::filesystem::remove(fileName));
}

// Tile

TEST(GeoPackageLibTests, GeoPackage_Tile_Str) {
    geopackage::Tile t{0,1,2};
    std::stringstream str;
    str << t;
    EXPECT_EQ("TILE (0, 1, 2)", str.str());
}

TEST(GeoPackageLibTests, GeoPackage_Min_Max_Zoom) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage geopackage { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    std::string name = "basemap";
    geopackage.createTileTable(name);
    geopackage.addTile(name, geopackage::Tile(0,0,0,"../../../data/tms/0/0/0.jpeg"));
    geopackage.addTile(name, geopackage::Tile(1,0,0,"../../../data/tms/1/0/0.jpeg"));
    geopackage.addTile(name, geopackage::Tile(1,0,1,"../../../data/tms/1/0/1.jpeg"));
    geopackage.addTile(name, geopackage::Tile(1,1,0,"../../../data/tms/1/1/0.jpeg"));
    geopackage.addTile(name, geopackage::Tile(1,1,1,"../../../data/tms/1/1/1.jpeg"));

    EXPECT_EQ(0, geopackage.getMinZoom(name));
    EXPECT_EQ(1, geopackage.getMaxZoom(name));

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_Count_Tiles) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage geopackage { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    std::string name = "basemap";
    geopackage.createTileTable(name);
    geopackage.addTile(name, geopackage::Tile(0,0,0,"../../../data/tms/0/0/0.jpeg"));
    geopackage.addTile(name, geopackage::Tile(1,0,0,"../../../data/tms/1/0/0.jpeg"));
    geopackage.addTile(name, geopackage::Tile(1,0,1,"../../../data/tms/1/0/1.jpeg"));
    geopackage.addTile(name, geopackage::Tile(1,1,0,"../../../data/tms/1/1/0.jpeg"));
    geopackage.addTile(name, geopackage::Tile(1,1,1,"../../../data/tms/1/1/1.jpeg"));

    EXPECT_EQ(1, geopackage.countTiles(name, 0));
    EXPECT_EQ(4, geopackage.countTiles(name, 1));
    EXPECT_EQ(5, geopackage.countTiles(name));

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_Add_Tile) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage geopackage { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    std::string name = "basemap";
    geopackage.createTileTable(name);
    EXPECT_FALSE(geopackage.getTile(name, 0,1,2));
    geopackage.addTile(name, geopackage::Tile{0,1,2,std::vector<geopackage::byte>{'a','b','c'}});
    EXPECT_TRUE(geopackage.getTile(name, 0,1,2));

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_Set_Tile) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage geopackage { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    std::string name = "basemap";
    geopackage.createTileTable(name);
    EXPECT_FALSE(geopackage.getTile(name, 0,1,2));
    geopackage.setTile(name, geopackage::Tile{0,1,2,std::vector<geopackage::byte>{'a','b','c'}});
    EXPECT_TRUE(geopackage.getTile(name, 0,1,2));
    EXPECT_EQ(1, geopackage.countTiles(name, 0));

    geopackage.setTile(name, geopackage::Tile{0,1,2,std::vector<geopackage::byte>{'a','b','c'}});
    EXPECT_TRUE(geopackage.getTile(name, 0,1,2));
    EXPECT_EQ(1, geopackage.countTiles(name, 0));

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_Add_Tile_File) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage geopackage { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    std::string name = "basemap";
    geopackage.createTileTable(name);

    geopackage.addTile(name, geopackage::Tile(0,0,0,"../../../data/tms/0/0/0.jpeg"));
    geopackage.addTile(name, geopackage::Tile(1,0,0,"../../../data/tms/1/0/0.jpeg"));
    geopackage.addTile(name, geopackage::Tile(1,0,1,"../../../data/tms/1/0/1.jpeg"));
    geopackage.addTile(name, geopackage::Tile(1,1,0,"../../../data/tms/1/1/0.jpeg"));
    geopackage.addTile(name, geopackage::Tile(1,1,1,"../../../data/tms/1/1/1.jpeg"));
    
    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_Update_Tile) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage geopackage { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    std::string name = "basemap";
    geopackage.createTileTable(name);

    EXPECT_FALSE(geopackage.getTile(name, 0,1,2));
    geopackage.addTile(name, geopackage::Tile{0,1,2,std::vector<geopackage::byte>{'a','b','c'}});
    EXPECT_TRUE(geopackage.getTile(name, 0,1,2));

    geopackage.updateTile(name, geopackage::Tile{0,1,2,std::vector<geopackage::byte>{'a','b','c','e','f','g'}});
    EXPECT_TRUE(geopackage.getTile(name, 0,1,2));

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_Delete_Tile) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage geopackage { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    std::string name = "basemap";
    geopackage.createTileTable(name);

    EXPECT_FALSE(geopackage.getTile(name, 0,1,2));
    geopackage.addTile(name, geopackage::Tile{0,1,2,std::vector<geopackage::byte>{'a','b','c'}});
    EXPECT_TRUE(geopackage.getTile(name, 0,1,2));

    geopackage.deleteTile(name, geopackage::Tile{0,1,2,std::vector<geopackage::byte>{}});  
    EXPECT_FALSE(geopackage.getTile(name, 0,1,2));    

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_Get_Tile) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage geopackage { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    std::string name = "basemap";
    geopackage.createTileTable(name);

    EXPECT_FALSE(geopackage.getTile(name, 0,1,2));
    geopackage.addTile(name, geopackage::Tile{0,1,2,std::vector<geopackage::byte>{'a','b','c'}});
    EXPECT_TRUE(geopackage.getTile(name, 0,1,2));
    EXPECT_EQ(0, geopackage.getTile(name, 0,1,2).value().zoom);
    EXPECT_EQ(1, geopackage.getTile(name, 0,1,2).value().column);
    EXPECT_EQ(2, geopackage.getTile(name, 0,1,2).value().row);
    EXPECT_EQ('a', geopackage.getTile(name, 0,1,2).value().data[0]);
    EXPECT_EQ('b', geopackage.getTile(name, 0,1,2).value().data[1]);
    EXPECT_EQ('c', geopackage.getTile(name, 0,1,2).value().data[2]);

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_Tiles_For_Zoom) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage geopackage { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    std::string name = "basemap";
    geopackage.createTileTable(name);

    geopackage.addTile(name, geopackage::Tile(0,0,0,"../../../data/tms/0/0/0.jpeg"));
    geopackage.addTile(name, geopackage::Tile(1,0,0,"../../../data/tms/1/0/0.jpeg"));
    geopackage.addTile(name, geopackage::Tile(1,0,1,"../../../data/tms/1/0/1.jpeg"));
    geopackage.addTile(name, geopackage::Tile(1,1,0,"../../../data/tms/1/1/0.jpeg"));
    geopackage.addTile(name, geopackage::Tile(1,1,1,"../../../data/tms/1/1/1.jpeg"));

    int counter = 0;    
    geopackage.tiles(name, 1, [&](geopackage::Tile& t) {
        counter++;
    });
    EXPECT_EQ(4, counter);

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, Tile_CreateGlobalGeodeticTileLayer) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage gpkg { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    gpkg.createGlobalGeodeticTileLayer("tiles", 256, 19);

    EXPECT_TRUE(gpkg.getSpatialRef(4326).has_value());
    EXPECT_TRUE(gpkg.getContent("tiles").has_value());
    EXPECT_TRUE(gpkg.getTileMatrixSet("tiles").has_value());
    int c = 0;
    gpkg.tileMatrices("tiles", [&](geopackage::TileMatrix& t) {
        c++;
    });
    EXPECT_EQ(19, c);

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, Tile_CreateGlobalMercatorTileLayer) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage gpkg { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    gpkg.createGlobalMercatorTileLayer("tiles", 512, 12);

    EXPECT_TRUE(gpkg.getSpatialRef(3857).has_value());
    EXPECT_TRUE(gpkg.getContent("tiles").has_value());
    EXPECT_TRUE(gpkg.getTileMatrixSet("tiles").has_value());
    int c = 0;
    gpkg.tileMatrices("tiles", [&](geopackage::TileMatrix& t) {
        c++;
    });
    EXPECT_EQ(12, c);

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, exportTilesToDirectory) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage gpkg { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    gpkg.createTileTable("tiles");
    gpkg.addTile("tiles",geopackage::Tile(0,0,0,"../../../data/tms/0/0/0.jpeg"));
    gpkg.addTile("tiles",geopackage::Tile(1,0,0,"../../../data/tms/1/0/0.jpeg"));
    gpkg.addTile("tiles",geopackage::Tile(1,0,1,"../../../data/tms/1/0/1.jpeg"));
    gpkg.addTile("tiles",geopackage::Tile(1,1,0,"../../../data/tms/1/1/0.jpeg"));
    gpkg.addTile("tiles",geopackage::Tile(1,1,1,"../../../data/tms/1/1/1.jpeg"));

    gpkg.exportTilesToDirectory("tiles", "jpeg", "tms");
    EXPECT_TRUE(std::filesystem::exists("tms/0/0/0.jpeg"));
    EXPECT_TRUE(std::filesystem::exists("tms/1/0/0.jpeg"));
    EXPECT_TRUE(std::filesystem::exists("tms/1/0/1.jpeg"));
    EXPECT_TRUE(std::filesystem::exists("tms/1/1/0.jpeg"));
    EXPECT_TRUE(std::filesystem::exists("tms/1/1/1.jpeg"));

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, loadTilesFromDirectory) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage gpkg { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    gpkg.createTileTable("tiles");
    gpkg.loadTilesFromDirectory("tiles", "../../../data/tms");
    EXPECT_TRUE(gpkg.getTile("tiles", 0,0,0));
    EXPECT_TRUE(gpkg.getTile("tiles",1,0,0));
    EXPECT_TRUE(gpkg.getTile("tiles",1,0,1));
    EXPECT_TRUE(gpkg.getTile("tiles",1,1,0));
    EXPECT_TRUE(gpkg.getTile("tiles",1,1,1));
    
    EXPECT_TRUE(std::filesystem::remove(fileName));
}

// Content

TEST(GeoPackageLibTests, Content_ToString) {
    geopackage::Content content{"cities", geopackage::DataType::FEATURES, "cities", "A Layer of cities", "2022-01-29T18:38:34.649Z", geopackage::Bounds{-180,-90,180,90}, 4326};
    std::stringstream str;
    str << content;
    EXPECT_EQ("CONTENT (tableName = cities, dataType = features, identifier = cities, description = A Layer of cities, lastChange = 2022-01-29T18:38:34.649Z, bounds = BOUNDS (-180, -90, 180, 90), srsId = 4326)", str.str());
}

TEST(GeoPackageLibTests, GeoPackage_Add_Content) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage gpkg { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    gpkg.addContent(geopackage::Content{"cities", geopackage::DataType::FEATURES, "cities", "A Layer of cities", "2022-01-29T18:38:34.649Z", geopackage::Bounds{-180,-90,180,90}, 4326});
    std::optional<geopackage::Content> c = gpkg.getContent("cities");
    EXPECT_TRUE(c.has_value());

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_Update_Content) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage geopackage { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    geopackage.addContent(geopackage::Content{"cities", geopackage::DataType::FEATURES, "cities", "A Layer of cities", "2022-01-29T18:38:34.649Z", geopackage::Bounds{-180,-90,180,90}, 4326});
    std::optional<geopackage::Content> c = geopackage.getContent("cities");
    EXPECT_TRUE(c.has_value());
    EXPECT_EQ("cities", c.value().getTableName());

    geopackage.updateContent(geopackage::Content{"cities", geopackage::DataType::FEATURES, "cities", "World wide cities", "2022-01-29T18:38:34.649Z", geopackage::Bounds{-180,-90,180,90}, 4326});
    std::optional<geopackage::Content> c2 = geopackage.getContent("cities");
    EXPECT_TRUE(c2.has_value());
    EXPECT_EQ("cities", c2.value().getTableName());

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_Set_Content) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage geopackage { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    geopackage.setContent(geopackage::Content{"cities", geopackage::DataType::FEATURES, "cities", "A Layer of cities", "2022-01-29T18:38:34.649Z", geopackage::Bounds{-180,-90,180,90}, 4326});
    std::optional<geopackage::Content> c = geopackage.getContent("cities");
    EXPECT_TRUE(c.has_value());
    EXPECT_EQ("cities", c.value().getTableName());

    geopackage.setContent(geopackage::Content{"cities", geopackage::DataType::FEATURES, "cities", "World wide cities", "2022-01-29T18:38:34.649Z", geopackage::Bounds{-180,-90,180,90}, 4326});
    std::optional<geopackage::Content> c2 = geopackage.getContent("cities");
    EXPECT_TRUE(c2.has_value());
    EXPECT_EQ("cities", c2.value().getTableName());

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_Delete_Content) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage geopackage { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    geopackage.addContent(geopackage::Content{"cities", geopackage::DataType::FEATURES, "cities", "A Layer of cities", "2022-01-29T18:38:34.649Z", geopackage::Bounds{-180,-90,180,90}, 4326});
    std::optional<geopackage::Content> c1 = geopackage.getContent("cities");
    EXPECT_TRUE(c1.has_value());
    EXPECT_EQ("cities", c1.value().getTableName());

    geopackage.deleteContent(c1.value());
    std::optional<geopackage::Content> c2 = geopackage.getContent("cities");
    EXPECT_FALSE(c2.has_value());

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_Get_Content) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage geopackage { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    std::optional<geopackage::Content> c1 = geopackage.getContent("Spatial Index");
    EXPECT_FALSE(c1.has_value());
    geopackage.addContent(geopackage::Content{"cities", geopackage::DataType::FEATURES, "cities", "A Layer of cities", "2022-01-29T18:38:34.649Z", geopackage::Bounds{-180,-90,180,90}, 4326});
    std::optional<geopackage::Content> c2 = geopackage.getContent("cities");
    EXPECT_TRUE(c2.has_value());

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_Contents) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage geopackage { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    geopackage.addContent(geopackage::Content{"cities", geopackage::DataType::FEATURES, "cities", "A Layer of cities", "2022-01-29T18:38:34.649Z", geopackage::Bounds{-180,-90,180,90}, 4326});
    geopackage.addContent(geopackage::Content{"rivers", geopackage::DataType::FEATURES, "rivers", "A Layer of rivers", "2022-01-29T18:38:34.649Z", geopackage::Bounds{-180,-90,180,90}, 4326});
    geopackage.addContent(geopackage::Content{"pacels", geopackage::DataType::FEATURES, "parcels", "A Layer of parcels", "2022-01-29T18:38:34.649Z", geopackage::Bounds{-180,-90,180,90}, 4326});
    
    int counter = 0;    
    geopackage.contents([&](geopackage::Content& e) {
        counter++;
    });
    EXPECT_EQ(3, counter);


    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_Contents_By_Type) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage geopackage { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    geopackage.addContent(geopackage::Content{"cities", geopackage::DataType::FEATURES, "cities", "A Layer of cities", "2022-01-29T18:38:34.649Z", geopackage::Bounds{-180,-90,180,90}, 4326});
    geopackage.addContent(geopackage::Content{"rivers", geopackage::DataType::FEATURES, "rivers", "A Layer of rivers", "2022-01-29T18:38:34.649Z", geopackage::Bounds{-180,-90,180,90}, 4326});
    geopackage.addContent(geopackage::Content{"pacels", geopackage::DataType::FEATURES, "parcels", "A Layer of parcels", "2022-01-29T18:38:34.649Z", geopackage::Bounds{-180,-90,180,90}, 4326});
    geopackage.addContent(geopackage::Content{"basemap", geopackage::DataType::TILES, "basemap", "A Basemap", "2022-01-29T18:38:34.649Z", geopackage::Bounds{-180,-90,180,90}, 4326});
    geopackage.addContent(geopackage::Content{"tiles", geopackage::DataType::TILES, "tiles", "A Tiles Basemap", "2022-01-29T18:38:34.649Z", geopackage::Bounds{-180,-90,180,90}, 4326});
    
    int counter = 0;    
    geopackage.contents(geopackage::DataType::TILES, [&](geopackage::Content& e) {
        counter++;
    });
    EXPECT_EQ(2, counter);

    counter = 0;    
    geopackage.contents(geopackage::DataType::FEATURES, [&](geopackage::Content& e) {
        counter++;
    });
    EXPECT_EQ(3, counter);


    EXPECT_TRUE(std::filesystem::remove(fileName));
}

// Feature

TEST(GeoPackageLibTests, GeoPackage_Feature_Table_Create) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage geopackage { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    geopackage::Schema schema{
        "cities",
        "id",
        geopackage::GeometryField{"geometry", geopackage::GeometryType::POINT, 4326},
        std::vector{
            geopackage::Field{"name", geopackage::FieldType::String},
            geopackage::Field{"population", geopackage::FieldType::Double}
        }
    };
    geopackage.createFeatureTable(schema);

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_Feature_Layer_Create) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage geopackage { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    geopackage::Schema schema{
        "cities",
        "id",
        geopackage::GeometryField{"geometry", geopackage::GeometryType::POINT, 4326},
        std::vector{
            geopackage::Field{"name", geopackage::FieldType::String},
            geopackage::Field{"population", geopackage::FieldType::Double}
        }
    };
    geopackage::Bounds bounds = geopackage::Bounds::getGeodeticBounds();
    geopackage.createFeatureLayer(schema, bounds);

    EXPECT_TRUE(geopackage.getContent("cities"));
    EXPECT_TRUE(geopackage.getGeometryColumn("cities"));

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_Feature_Add) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage geopackage { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    geopackage.addContent(geopackage::Content{"cities", geopackage::DataType::FEATURES, "cities", "A Layer of cities", "2022-01-29T18:38:34.649Z", geopackage::Bounds{-180,-90,180,90}, 4326});

    geopackage.addGeometryColumn(geopackage::GeometryColumn{"cities", "geometry", geopackage::GeometryType::POINT, 4326, geopackage::Dimension::Three});

    geopackage::Schema schema{
        "cities",
        "id",
        geopackage::GeometryField{"geometry", geopackage::GeometryType::POINT, 4326},
        std::vector{
            geopackage::Field{"name", geopackage::FieldType::String},
            geopackage::Field{"population", geopackage::FieldType::Double}
        }
    };
    geopackage.createFeatureTable(schema);

    EXPECT_EQ(0, geopackage.countFeatures("cities"));
    geopackage.addFeature("cities", geopackage::Feature{
        std::make_unique<geopackage::Point>(-122, 47),
        std::map<std::string, std::any> {{"population", 737000}, {"name", std::string{"One"}}}
    });
    EXPECT_EQ(1, geopackage.countFeatures("cities"));

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_Get_Schema) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage geopackage { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    geopackage.addContent(geopackage::Content{"cities", geopackage::DataType::FEATURES, "cities", "A Layer of cities", "2022-01-29T18:38:34.649Z", geopackage::Bounds{-180,-90,180,90}, 4326});

    geopackage.addGeometryColumn(geopackage::GeometryColumn{"cities", "geometry", geopackage::GeometryType::POINT, 4326, geopackage::Dimension::Three});

    geopackage.createFeatureTable(geopackage::Schema{
        "cities",
        "id",
        geopackage::GeometryField{"geometry", geopackage::GeometryType::POINT, 4326},
        std::vector{
            geopackage::Field{"name", geopackage::FieldType::String},
            geopackage::Field{"population", geopackage::FieldType::Double}
        }
    });

    geopackage::Schema schema = geopackage.getSchema("cities");
    EXPECT_EQ("cities", schema.getName());
    EXPECT_EQ("id", schema.getKey());
    EXPECT_EQ("geometry", schema.getGeometryField().getName());
    EXPECT_EQ(geopackage::GeometryType::POINT, schema.getGeometryField().getType());
    EXPECT_EQ(4326, schema.getGeometryField().getSrsId());
    EXPECT_EQ(2, schema.getFields().size());

    for(auto fld : schema.getFields()) {
        if (fld.getName() == "name") {
            EXPECT_EQ(geopackage::FieldType::String, fld.getType());
        } else {
            EXPECT_EQ("population", fld.getName());;
            EXPECT_EQ(geopackage::FieldType::Double, fld.getType());
        }
    }

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_Feature_Update) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage geopackage { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    // Set up

    geopackage.addContent(geopackage::Content{"cities", geopackage::DataType::FEATURES, "cities", "A Layer of cities", "2022-01-29T18:38:34.649Z", geopackage::Bounds{-180,-90,180,90}, 4326});

    geopackage.addGeometryColumn(geopackage::GeometryColumn{"cities", "geometry", geopackage::GeometryType::POINT, 4326, geopackage::Dimension::Three});

    geopackage::Schema schema{
        "cities",
        "id",
        geopackage::GeometryField{"geometry", geopackage::GeometryType::POINT, 4326},
        std::vector{
            geopackage::Field{"name", geopackage::FieldType::String},
            geopackage::Field{"population", geopackage::FieldType::Double}
        }
    };
    geopackage.createFeatureTable(schema);

    // Add Feature

    EXPECT_EQ(0, geopackage.countFeatures("cities"));
    geopackage.addFeature("cities", geopackage::Feature{
        std::make_unique<geopackage::Point>(-122, 47),
        std::map<std::string, std::any> {{"population", 737000}, {"name", std::string{"One"}}}
    });
    EXPECT_EQ(1, geopackage.countFeatures("cities"));

    std::optional<geopackage::Feature> feature = geopackage.getFeature("cities", 1);
    EXPECT_TRUE(feature.has_value());
    geopackage::Feature f = feature.value();
    EXPECT_EQ("POINT (-122 47)", f.getGeometry()->wkt());
    EXPECT_EQ(1, f.getId().value());
    EXPECT_EQ("One", std::any_cast<std::string>(f.getAttributes()["name"]));
    EXPECT_EQ(737000, std::any_cast<double>(f.getAttributes()["population"]));

    // Update Feature

    f.setAttribute("name", "One Updated").setAttribute("population", 123);
    f.setGeometry(std::make_unique<geopackage::Point>(-123.45, 47.59));
    geopackage.updateFeature("cities", f);

    EXPECT_EQ(1, geopackage.countFeatures("cities"));
    std::optional<geopackage::Feature> featureUpdated = geopackage.getFeature("cities", f.getId().value());
    EXPECT_TRUE(featureUpdated.has_value());
    EXPECT_EQ(1, featureUpdated->getId().value());
    EXPECT_EQ("POINT (-123.45 47.59)", featureUpdated->getGeometry()->wkt());
    EXPECT_EQ("One Updated", std::any_cast<std::string>(featureUpdated->getAttributes()["name"]));
    EXPECT_EQ(123, std::any_cast<double>(featureUpdated->getAttributes()["population"]));

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_Feature_Set) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage geopackage { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    // Set up

    geopackage.addContent(geopackage::Content{"cities", geopackage::DataType::FEATURES, "cities", "A Layer of cities", "2022-01-29T18:38:34.649Z", geopackage::Bounds{-180,-90,180,90}, 4326});

    geopackage.addGeometryColumn(geopackage::GeometryColumn{"cities", "geometry", geopackage::GeometryType::POINT, 4326, geopackage::Dimension::Three});

    geopackage::Schema schema{
        "cities",
        "id",
        geopackage::GeometryField{"geometry", geopackage::GeometryType::POINT, 4326},
        std::vector{
            geopackage::Field{"name", geopackage::FieldType::String},
            geopackage::Field{"population", geopackage::FieldType::Double}
        }
    };
    geopackage.createFeatureTable(schema);

    // Add Feature

    EXPECT_EQ(0, geopackage.countFeatures("cities"));
    geopackage.setFeature("cities", geopackage::Feature{
        std::make_unique<geopackage::Point>(-122, 47),
        std::map<std::string, std::any> {{"population", 737000}, {"name", std::string{"One"}}}
    });
    EXPECT_EQ(1, geopackage.countFeatures("cities"));

    std::optional<geopackage::Feature> feature = geopackage.getFeature("cities", 1);
    EXPECT_TRUE(feature.has_value());
    geopackage::Feature f = feature.value();
    EXPECT_EQ("POINT (-122 47)", f.getGeometry()->wkt());
    EXPECT_EQ(1, f.getId().value());
    EXPECT_EQ("One", std::any_cast<std::string>(f.getAttributes()["name"]));
    EXPECT_EQ(737000, std::any_cast<double>(f.getAttributes()["population"]));

    // Update Feature

    f.setAttribute("name", "One Updated").setAttribute("population", 123);
    f.setGeometry(std::make_unique<geopackage::Point>(-123.45, 47.59));
    geopackage.setFeature("cities", f);

    EXPECT_EQ(1, geopackage.countFeatures("cities"));
    std::optional<geopackage::Feature> featureUpdated = geopackage.getFeature("cities", f.getId().value());
    EXPECT_TRUE(featureUpdated.has_value());
    EXPECT_EQ(1, featureUpdated->getId().value());
    EXPECT_EQ("POINT (-123.45 47.59)", featureUpdated->getGeometry()->wkt());
    EXPECT_EQ("One Updated", std::any_cast<std::string>(featureUpdated->getAttributes()["name"]));
    EXPECT_EQ(123, std::any_cast<double>(featureUpdated->getAttributes()["population"]));

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_Feature_Get) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage geopackage { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    geopackage.addContent(geopackage::Content{"cities", geopackage::DataType::FEATURES, "cities", "A Layer of cities", "2022-01-29T18:38:34.649Z", geopackage::Bounds{-180,-90,180,90}, 4326});

    geopackage.addGeometryColumn(geopackage::GeometryColumn{"cities", "geometry", geopackage::GeometryType::POINT, 4326, geopackage::Dimension::Three});

    geopackage::Schema schema{
        "cities",
        "id",
        geopackage::GeometryField{"geometry", geopackage::GeometryType::POINT, 4326},
        std::vector{
            geopackage::Field{"name", geopackage::FieldType::String},
            geopackage::Field{"population", geopackage::FieldType::Double}
        }
    };
    geopackage.createFeatureTable(schema);

    EXPECT_EQ(0, geopackage.countFeatures("cities"));
    geopackage.addFeature("cities", geopackage::Feature{
        std::make_unique<geopackage::Point>(-122, 47),
        std::map<std::string, std::any> {{"population", 737000}, {"name", std::string{"One"}}}
    });
    EXPECT_EQ(1, geopackage.countFeatures("cities"));

    std::optional<geopackage::Feature> feature = geopackage.getFeature("cities", 1);
    EXPECT_TRUE(feature.has_value());
    EXPECT_EQ("POINT (-122 47)", feature->getGeometry()->wkt());
    EXPECT_EQ("One", std::any_cast<std::string>(feature->getAttributes()["name"]));
    EXPECT_EQ(737000, std::any_cast<double>(feature->getAttributes()["population"]));
    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_Feature_GetAll) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage geopackage { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    geopackage.addContent(geopackage::Content{"cities", geopackage::DataType::FEATURES, "cities", "A Layer of cities", "2022-01-29T18:38:34.649Z", geopackage::Bounds{-180,-90,180,90}, 4326});

    geopackage.addGeometryColumn(geopackage::GeometryColumn{"cities", "geometry", geopackage::GeometryType::POINT, 4326, geopackage::Dimension::Three});

    geopackage::Schema schema{
        "cities",
        "id",
        geopackage::GeometryField{"geometry", geopackage::GeometryType::POINT, 4326},
        std::vector{
            geopackage::Field{"name", geopackage::FieldType::String},
            geopackage::Field{"population", geopackage::FieldType::Double}
        }
    };
    geopackage.createFeatureTable(schema);

    EXPECT_EQ(0, geopackage.countFeatures("cities"));
    geopackage.addFeature("cities", geopackage::Feature{
        std::make_unique<geopackage::Point>(-122, 47),
        std::map<std::string, std::any> {{"population", 737000}, {"name", std::string{"One"}}}
    });
    EXPECT_EQ(1, geopackage.countFeatures("cities"));
    geopackage.addFeature("cities", geopackage::Feature{
        std::make_unique<geopackage::Point>(-123, 48),
        std::map<std::string, std::any> {{"population", 123}, {"name", std::string{"Two"}}}
    });
    EXPECT_EQ(2, geopackage.countFeatures("cities"));

    int counter = 0;    
    geopackage.features("cities", [&](geopackage::Feature& f) {
        counter++;
    });
    EXPECT_EQ(2, counter);

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_Feature_Delete) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage geopackage { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    // Set up

    geopackage.addContent(geopackage::Content{"cities", geopackage::DataType::FEATURES, "cities", "A Layer of cities", "2022-01-29T18:38:34.649Z", geopackage::Bounds{-180,-90,180,90}, 4326});

    geopackage.addGeometryColumn(geopackage::GeometryColumn{"cities", "geometry", geopackage::GeometryType::POINT, 4326, geopackage::Dimension::Three});

    geopackage::Schema schema{
        "cities",
        "id",
        geopackage::GeometryField{"geometry", geopackage::GeometryType::POINT, 4326},
        std::vector{
            geopackage::Field{"name", geopackage::FieldType::String},
            geopackage::Field{"population", geopackage::FieldType::Double}
        }
    };
    geopackage.createFeatureTable(schema);

    // Add

    EXPECT_EQ(0, geopackage.countFeatures("cities"));
    geopackage.addFeature("cities", geopackage::Feature{
        std::make_unique<geopackage::Point>(-122, 47),
        std::map<std::string, std::any> {{"population", 737000}, {"name", std::string{"One"}}}
    });
    EXPECT_EQ(1, geopackage.countFeatures("cities"));
    
    geopackage.addFeature("cities", geopackage::Feature{
        std::make_unique<geopackage::Point>(-123, 48),
        std::map<std::string, std::any> {{"population", 123}, {"name", std::string{"Two"}}}
    });
    EXPECT_EQ(2, geopackage.countFeatures("cities"));

    // Delete
    geopackage.deleteFeature("cities", geopackage.getFeature("cities", 1).value());
    EXPECT_EQ(1, geopackage.countFeatures("cities"));
    geopackage.deleteFeature("cities", geopackage.getFeature("cities", 2).value());
    EXPECT_EQ(0, geopackage.countFeatures("cities"));

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_Feature_DeleteAll) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage geopackage { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    // Set up

    geopackage.addContent(geopackage::Content{"cities", geopackage::DataType::FEATURES, "cities", "A Layer of cities", "2022-01-29T18:38:34.649Z", geopackage::Bounds{-180,-90,180,90}, 4326});

    geopackage.addGeometryColumn(geopackage::GeometryColumn{"cities", "geometry", geopackage::GeometryType::POINT, 4326, geopackage::Dimension::Three});

    geopackage::Schema schema{
        "cities",
        "id",
        geopackage::GeometryField{"geometry", geopackage::GeometryType::POINT, 4326},
        std::vector{
            geopackage::Field{"name", geopackage::FieldType::String},
            geopackage::Field{"population", geopackage::FieldType::Double}
        }
    };
    geopackage.createFeatureTable(schema);

    // Add

    EXPECT_EQ(0, geopackage.countFeatures("cities"));
    geopackage.addFeature("cities", geopackage::Feature{
        std::make_unique<geopackage::Point>(-122, 47),
        std::map<std::string, std::any> {{"population", 737000}, {"name", std::string{"One"}}}
    });
    EXPECT_EQ(1, geopackage.countFeatures("cities"));
    
    geopackage.addFeature("cities", geopackage::Feature{
        std::make_unique<geopackage::Point>(-123, 48),
        std::map<std::string, std::any> {{"population", 123}, {"name", std::string{"Two"}}}
    });
    EXPECT_EQ(2, geopackage.countFeatures("cities"));

    // Delete
    geopackage.deleteAllFeatures("cities");
    EXPECT_EQ(0, geopackage.countFeatures("cities"));

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

// Layer Style

TEST(GeoPackageLibTests, GeoPackage_Add_LayerStyle) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage gpkg { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    auto layerStyle = geopackage::LayerStyle {
        "", "", "cities", "geom", "cities_default", "", "<sld></sld>", true, "The default cities style", "admin", ""
    };

    gpkg.addLayerStyle(layerStyle);
    std::optional<geopackage::LayerStyle> ls = gpkg.getLayerStyle(1);
    EXPECT_TRUE(ls.has_value());

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_Update_LayerStyle) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage geopackage { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    geopackage.addLayerStyle(geopackage::LayerStyle {
        "", "", "cities", "geom", "cities_default", "", "<sld></sld>", true, "The default cities style", "admin", ""
    });
    std::optional<geopackage::LayerStyle> s1 = geopackage.getLayerStyle(1);
    EXPECT_TRUE(s1.has_value());
    EXPECT_EQ("cities", s1.value().getTableName());

    geopackage.updateLayerStyle(geopackage::LayerStyle {
        1, "", "", "places", "geom", "cities_default", "", "<sld></sld>", true, "The default cities style", "admin", "", ""
    });
    std::optional<geopackage::LayerStyle> s2 = geopackage.getLayerStyle(1);
    EXPECT_TRUE(s2.has_value());
    EXPECT_EQ("places", s2.value().getTableName());

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_Get_LayerStyle) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage gpkg { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    auto layerStyle = geopackage::LayerStyle {
        "", "", "cities", "geom", "cities_default", "", "<sld></sld>", true, "The default cities style", "admin", ""
    };

    gpkg.addLayerStyle(layerStyle);
    std::optional<geopackage::LayerStyle> ls = gpkg.getLayerStyle(1);
    EXPECT_TRUE(ls.has_value());

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_Get_Default_LayerStyle) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage gpkg { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    gpkg.addLayerStyle(geopackage::LayerStyle {
        "", "", "cities", "geom", "cities_default", "", "<sld></sld>", true, "The default cities style", "admin", ""
    });
    gpkg.addLayerStyle(geopackage::LayerStyle {
        "", "", "cities", "geom", "cities_blue", "", "<sld></sld>", false, "The b clueities style", "admin", ""
    });
    gpkg.addLayerStyle(geopackage::LayerStyle {
        "", "", "riviers", "geom", "rivers_blue", "", "<sld></sld>", false, "The blue rivers style", "admin", ""
    });
    std::optional<geopackage::LayerStyle> ls = gpkg.getDefaultLayerStyle("cities");
    EXPECT_TRUE(ls.has_value());
    EXPECT_EQ("cities", ls->getTableName());
    EXPECT_EQ("cities_default", ls->getStyleName());

    EXPECT_FALSE(gpkg.getDefaultLayerStyle("rivers").has_value());

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_Delete_LayerStyle) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage gpkg { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    auto layerStyle = geopackage::LayerStyle {
        "", "", "cities", "geom", "cities_default", "", "<sld></sld>", true, "The default cities style", "admin", ""
    };

    gpkg.addLayerStyle(layerStyle);
    std::optional<geopackage::LayerStyle> ls = gpkg.getLayerStyle(1);
    EXPECT_TRUE(ls.has_value());

    gpkg.deleteLayerStyle(layerStyle);

    std::optional<geopackage::LayerStyle> lsAfterDelete = gpkg.getLayerStyle(1);
    EXPECT_TRUE(lsAfterDelete.has_value());

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_Get_LayerStyles) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage gpkg { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    gpkg.addLayerStyle(geopackage::LayerStyle {
        "", "", "cities", "geom", "cities_default", "", "<sld></sld>", true, "The default cities style", "admin", ""
    });
    gpkg.addLayerStyle(geopackage::LayerStyle {
        "", "", "riviers", "geom", "blue_rivers", "", "<sld></sld>", true, "The default rivers style", "admin", ""
    });
    
    int counter = 0;    
    gpkg.layerStyles([&](geopackage::LayerStyle& s) {
        counter++;
    });
    EXPECT_EQ(2, counter);

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_Get_LayerStyles_For_Table) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage gpkg { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    gpkg.addLayerStyle(geopackage::LayerStyle {
        "", "", "cities", "geom", "cities_default", "", "<sld></sld>", true, "The default cities style", "admin", ""
    });
    gpkg.addLayerStyle(geopackage::LayerStyle {
        "", "", "cities", "geom", "cities_red", "", "<sld></sld>", true, "The red cities style", "admin", ""
    });
    gpkg.addLayerStyle(geopackage::LayerStyle {
        "", "", "rivers", "geom", "blue_rivers", "", "<sld></sld>", true, "The default rivers style", "admin", ""
    });
    
    int counter = 0;    
    gpkg.layerStylesForLayer("cities", [&](geopackage::LayerStyle& s) {
        counter++;
    });
    EXPECT_EQ(2, counter);

    counter = 0;    
    gpkg.layerStylesForLayer("rivers", [&](geopackage::LayerStyle& s) {
        counter++;
    });
    EXPECT_EQ(1, counter);

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_Add_Index_Extension) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage gpkg { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    gpkg.addGeometryColumn(geopackage::GeometryColumn{"cities", "geometry", geopackage::GeometryType::POINT, 4326, geopackage::Dimension::Three});

    gpkg.addIndexExtension("cities");

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_Add_Index) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage gpkg { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    gpkg.addGeometryColumn(geopackage::GeometryColumn{"cities", "geometry", geopackage::GeometryType::POINT, 4326, geopackage::Dimension::Three});

    gpkg.addIndexExtension("cities");
    gpkg.addIndex("cities", 1, geopackage::Bounds{0,0,10,10});
    gpkg.addIndex("cities", 2, geopackage::Bounds{5,5,15,15});

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_Delete_Index) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage gpkg { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    gpkg.addGeometryColumn(geopackage::GeometryColumn{"cities", "geometry", geopackage::GeometryType::POINT, 4326, geopackage::Dimension::Three});

    gpkg.addIndexExtension("cities");
    gpkg.addIndex("cities", 1, geopackage::Bounds{0,0,10,10});
    gpkg.addIndex("cities", 2, geopackage::Bounds{5,5,15,15});
    gpkg.deleteIndex("cities");

    EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageLibTests, GeoPackage_Index_Layer) {
    const std::string fileName = "data.gpkg";
    geopackage::GeoPackage gpkg { fileName };
    EXPECT_TRUE(std::filesystem::exists(fileName));

    // Set up

    gpkg.addContent(geopackage::Content{"cities", geopackage::DataType::FEATURES, "cities", "A Layer of cities", "2022-01-29T18:38:34.649Z", geopackage::Bounds{-180,-90,180,90}, 4326});

    gpkg.addGeometryColumn(geopackage::GeometryColumn{"cities", "geometry", geopackage::GeometryType::POINT, 4326, geopackage::Dimension::Three});

    geopackage::Schema schema{
        "cities",
        "id",
        geopackage::GeometryField{"geometry", geopackage::GeometryType::POINT, 4326},
        std::vector{
            geopackage::Field{"name", geopackage::FieldType::String},
            geopackage::Field{"population", geopackage::FieldType::Double}
        }
    };
    gpkg.createFeatureTable(schema);

    // Add

    EXPECT_EQ(0, gpkg.countFeatures("cities"));
    gpkg.addFeature("cities", geopackage::Feature{
        std::make_unique<geopackage::Point>(-122, 47),
        std::map<std::string, std::any> {{"population", 737000}, {"name", std::string{"One"}}}
    });
    EXPECT_EQ(1, gpkg.countFeatures("cities"));
    
    gpkg.addFeature("cities", geopackage::Feature{
        std::make_unique<geopackage::Point>(-123, 48),
        std::map<std::string, std::any> {{"population", 123}, {"name", std::string{"Two"}}}
    });
    EXPECT_EQ(2, gpkg.countFeatures("cities"));

    gpkg.addIndexExtension("cities");
    gpkg.indexLayer("cities");

    EXPECT_TRUE(std::filesystem::remove(fileName));
}