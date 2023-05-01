#include <sstream>
#include <iostream>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "tile/DeleteTileCommand.hpp"
#include "gtest/gtest.h"

TEST(GeoPackageCliTests, DeleteTileCommand) {
  
  const std::string fileName = "data.gpkg";
  geopackage::GeoPackage gpkg { fileName };
  EXPECT_TRUE(std::filesystem::exists(fileName));
  
  gpkg.createTileTable("tiles");
  gpkg.addTile("tiles", geopackage::Tile(0,0,0,"../../../data/tms/0/0/0.jpeg"));

  CLI::App app{"GeoPackageCPP CLI"};  

  Commands commands;
  DeleteTileCommand cmd{&app};
  commands.add(&cmd);

  int argc = 12;
  char const *argv[12] = {
    "geopackage-cli", "tile-delete", 
    "-f", "data.gpkg", 
    "-n", "tiles",
    "-z", "0", 
    "-c", "0", 
    "-r", "0"
  };

  app.parse(argc, argv);

  std::istringstream instream;
  std::ostringstream outstream;

  cmd.execute(instream, outstream);
  EXPECT_FALSE(gpkg.getTile("tiles",0,0,0));
  
  EXPECT_TRUE(std::filesystem::remove(fileName));
}