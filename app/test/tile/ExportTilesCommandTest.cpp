#include <sstream>
#include <iostream>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "tile/ExportTilesCommand.hpp"
#include "gtest/gtest.h"

TEST(GeoPackageCliTests, ExportTilesCommand) {
  
  const std::string fileName = "data.gpkg";
  geopackage::GeoPackage gpkg { fileName };
  EXPECT_TRUE(std::filesystem::exists(fileName));
  
  gpkg.createTileTable("tiles");
  // 0 
  gpkg.addTile("tiles", geopackage::Tile(0,0,0,"../../../data/tms/0/0/0.jpeg"));
  // 1
  gpkg.addTile("tiles", geopackage::Tile(1,0,0,"../../../data/tms/1/0/0.jpeg"));
  gpkg.addTile("tiles", geopackage::Tile(1,0,1,"../../../data/tms/1/0/1.jpeg"));
  gpkg.addTile("tiles", geopackage::Tile(1,1,0,"../../../data/tms/1/1/0.jpeg"));
  gpkg.addTile("tiles", geopackage::Tile(1,1,1,"../../../data/tms/1/1/1.jpeg"));

  CLI::App app{"GeoPackageCPP CLI"};  

  Commands commands;
  ExportTilesCommand cmd{&app};
  commands.add(&cmd);

  int argc = 10;
  char const *argv[10] = {
    "geopackage-cli", "tile-export", 
    "-f", "data.gpkg", 
    "-n", "tiles",
    "-d", "tiles", 
    "-m", "jpeg"
  };

  app.parse(argc, argv);

  std::istringstream instream;
  std::ostringstream outstream;

  cmd.execute(instream, outstream);

  EXPECT_TRUE(std::filesystem::exists("tiles/0/0/0.jpeg"));
  EXPECT_TRUE(std::filesystem::exists("tiles/1/0/0.jpeg"));
  EXPECT_TRUE(std::filesystem::exists("tiles/1/0/1.jpeg"));
  EXPECT_TRUE(std::filesystem::exists("tiles/1/1/0.jpeg"));
  EXPECT_TRUE(std::filesystem::exists("tiles/1/1/1.jpeg"));
  
  EXPECT_TRUE(std::filesystem::remove(fileName));
}