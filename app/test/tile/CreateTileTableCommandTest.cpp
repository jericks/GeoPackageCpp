#include <sstream>
#include <iostream>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "tile/CreateTileTableCommand.hpp"
#include "gtest/gtest.h"

TEST(GeoPackageCliTests, CreateTileTableCommand) {
  
  const std::string fileName = "data.gpkg";
  geopackage::GeoPackage gpkg { fileName };
  EXPECT_TRUE(std::filesystem::exists(fileName));
  
  CLI::App app{"GeoPackageCPP CLI"};  

  Commands commands;
  CreateTileTableCommand cmd{&app};
  commands.add(&cmd);

  int argc = 6;
  char const *argv[6] = {
    "geopackage-cli", "tiletable-create", 
    "-f", "data.gpkg", 
    "-n", "world"
  };

  app.parse(argc, argv);

  std::istringstream instream;
  std::ostringstream outstream;

  cmd.execute(instream, outstream);

  gpkg.addTile("world", geopackage::Tile{0,0,0});
  EXPECT_TRUE(gpkg.getTile("world", 0,0,0).has_value());
  
  EXPECT_TRUE(std::filesystem::remove(fileName));
}