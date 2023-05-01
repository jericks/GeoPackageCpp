#include <sstream>
#include <iostream>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "tile/GetTileCommand.hpp"
#include "gtest/gtest.h"

TEST(GeoPackageCliTests, GetTileCommand) {
  
  const std::string fileName = "data.gpkg";
  geopackage::GeoPackage gpkg { fileName };
  EXPECT_TRUE(std::filesystem::exists(fileName));
  
  gpkg.createTileTable("tiles");
  gpkg.addTile("tiles", geopackage::Tile(0,0,0,"../../../data/tms/0/0/0.jpeg"));

  CLI::App app{"GeoPackageCPP CLI"};  

  Commands commands;
  GetTileCommand cmd{&app};
  commands.add(&cmd);

  int argc = 14;
  char const *argv[14] = {
    "geopackage-cli", "tile-get", 
    "-f", "data.gpkg", 
    "-n", "tiles",
    "-z", "0", 
    "-c", "0", 
    "-r", "0", 
    "-o", "0.jpeg"
  };

  app.parse(argc, argv);

  std::istringstream instream;
  std::ostringstream outstream;

  cmd.execute(instream, outstream);
  EXPECT_TRUE(std::filesystem::exists("0.jpeg"));
  
  EXPECT_TRUE(std::filesystem::remove(fileName));
}