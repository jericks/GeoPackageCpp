#include <sstream>
#include <iostream>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "tile/SetTileCommand.hpp"
#include "gtest/gtest.h"

TEST(GeoPackageCliTests, SetTileCommand) {
  
  const std::string fileName = "data.gpkg";
  geopackage::GeoPackage gpkg { fileName };
  EXPECT_TRUE(std::filesystem::exists(fileName));
  
  gpkg.createTileTable("tiles");

  CLI::App app{"GeoPackageCPP CLI"};  

  Commands commands;
  SetTileCommand cmd{&app};
  commands.add(&cmd);

  int argc = 14;
  char const *argv[14] = {
    "geopackage-cli", "tile-set", 
    "-f", "data.gpkg", 
    "-n", "tiles",
    "-z", "0", 
    "-c", "0", 
    "-r", "0", 
    "-i", "../../../data/tms/0/0/0.jpeg"
  };

  app.parse(argc, argv);

  std::istringstream instream;
  std::ostringstream outstream;

  cmd.execute(instream, outstream);
  EXPECT_TRUE(gpkg.getTile("tiles",0,0,0));
  
  EXPECT_TRUE(std::filesystem::remove(fileName));
}