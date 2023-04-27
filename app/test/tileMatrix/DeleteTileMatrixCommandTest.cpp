#include <sstream>
#include <iostream>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "tileMatrix/DeleteTileMatrixCommand.hpp"
#include "gtest/gtest.h"

TEST(GeoPackageCliTests, DeleteTileMatrixCommand_All) {
  
  const std::string fileName = "data.gpkg";
  geopackage::GeoPackage gpkg { fileName };
  EXPECT_TRUE(std::filesystem::exists(fileName));
  
  gpkg.addTileMatrix(geopackage::TileMatrix{"basemap", 0, geopackage::Size<int>{2, 2}, geopackage::Size<int>{256, 256}, geopackage::Size<double>{2.0, 2.0}});
  gpkg.addTileMatrix(geopackage::TileMatrix{"basemap", 1, geopackage::Size<int>{4, 4}, geopackage::Size<int>{256, 256}, geopackage::Size<double>{1.0, 1.0}});
  gpkg.addTileMatrix(geopackage::TileMatrix{"basemap", 2, geopackage::Size<int>{8, 8}, geopackage::Size<int>{256, 256}, geopackage::Size<double>{0.5, 0.5}});
    
  CLI::App app{"GeoPackageCPP CLI"};  

  Commands commands;
  DeleteTileMatrixCommand cmd{&app};
  commands.add(&cmd);

  int argc = 6;
  char const *argv[6] = {"geopackage-cli", "tilematrix-delete", "-f", "data.gpkg", "-n", "basemap"};

  app.parse(argc, argv);

  std::istringstream instream;
  std::ostringstream outstream;

  cmd.execute(instream, outstream);

  EXPECT_FALSE(gpkg.getTileMatrix("basemap", 0).has_value());
  EXPECT_FALSE(gpkg.getTileMatrix("basemap", 1).has_value());
  EXPECT_FALSE(gpkg.getTileMatrix("basemap", 2).has_value());
  

  EXPECT_TRUE(std::filesystem::remove(fileName));
}

TEST(GeoPackageCliTests, DeleteTileMatrixCommand_Zoom) {
  
  const std::string fileName = "data.gpkg";
  geopackage::GeoPackage gpkg { fileName };
  EXPECT_TRUE(std::filesystem::exists(fileName));
  
  gpkg.addTileMatrix(geopackage::TileMatrix{"basemap", 0, geopackage::Size<int>{2, 2}, geopackage::Size<int>{256, 256}, geopackage::Size<double>{2.0, 2.0}});
  gpkg.addTileMatrix(geopackage::TileMatrix{"basemap", 1, geopackage::Size<int>{4, 4}, geopackage::Size<int>{256, 256}, geopackage::Size<double>{1.0, 1.0}});
  gpkg.addTileMatrix(geopackage::TileMatrix{"basemap", 2, geopackage::Size<int>{8, 8}, geopackage::Size<int>{256, 256}, geopackage::Size<double>{0.5, 0.5}});
    
  CLI::App app{"GeoPackageCPP CLI"};  

  Commands commands;
  DeleteTileMatrixCommand cmd{&app};
  commands.add(&cmd);

  int argc = 8;
  char const *argv[8] = {"geopackage-cli", "tilematrix-delete", "-f", "data.gpkg", "-n", "basemap", "-z", "1"};

  app.parse(argc, argv);

  std::istringstream instream;
  std::ostringstream outstream;

  cmd.execute(instream, outstream);

  EXPECT_TRUE(gpkg.getTileMatrix("basemap", 0).has_value());
  EXPECT_FALSE(gpkg.getTileMatrix("basemap", 1).has_value());
  EXPECT_TRUE(gpkg.getTileMatrix("basemap", 2).has_value());

  EXPECT_TRUE(std::filesystem::remove(fileName));
}