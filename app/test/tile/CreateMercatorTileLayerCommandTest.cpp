#include <sstream>
#include <iostream>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "tile/CreateMercatorTileLayerCommand.hpp"
#include "gtest/gtest.h"

TEST(GeoPackageCliTests, CreateMercatorTileLayerCommand) {
  
  const std::string fileName = "data.gpkg";
  geopackage::GeoPackage gpkg { fileName };
  EXPECT_TRUE(std::filesystem::exists(fileName));
  
  CLI::App app{"GeoPackageCPP CLI"};  

  Commands commands;
  CreateMercatorTileLayerCommand cmd{&app};
  commands.add(&cmd);

  int argc = 10;
  char const *argv[10] = {
    "geopackage-cli", "tile-mercator-create", 
    "-f", "data.gpkg", 
    "-n", "world",
    "-s", "256",
    "-z", "19"
  };

  app.parse(argc, argv);

  std::istringstream instream;
  std::ostringstream outstream;

  cmd.execute(instream, outstream);

  EXPECT_TRUE(gpkg.getSpatialRef(3857));
  EXPECT_TRUE(gpkg.getContent("world"));
  EXPECT_TRUE(gpkg.getTileMatrixSet("world"));
  int counter = 0;
  gpkg.tileMatrices("world", [&](auto &tileMtarix) {
      counter++;
  });
  EXPECT_EQ(19, counter);

  gpkg.addTile("world", geopackage::Tile{0,0,0});
  EXPECT_TRUE(gpkg.getTile("world", 0,0,0).has_value());
  
  EXPECT_TRUE(std::filesystem::remove(fileName));
}