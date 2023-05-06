#include <sstream>
#include <iostream>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "tile/ImportTilesCommand.hpp"
#include "gtest/gtest.h"

TEST(GeoPackageCliTests, ImportTilesCommand) {
  
  const std::string fileName = "data.gpkg";
  geopackage::GeoPackage gpkg { fileName };
  EXPECT_TRUE(std::filesystem::exists(fileName));
  
  gpkg.createTileTable("tiles");

  CLI::App app{"GeoPackageCPP CLI"};  

  Commands commands;
  ImportTilesCommand cmd{&app};
  commands.add(&cmd);

  int argc = 8;
  char const *argv[8] = {
    "geopackage-cli", "tile-import", 
    "-f", "data.gpkg", 
    "-n", "tiles",
    "-d", "../../../data/tms"
  };

  app.parse(argc, argv);

  std::istringstream instream;
  std::ostringstream outstream;

  cmd.execute(instream, outstream);

  // 0
  EXPECT_TRUE(gpkg.getTile("tiles",0,0,0));

  // 1
  EXPECT_TRUE(gpkg.getTile("tiles",1,0,0));
  EXPECT_TRUE(gpkg.getTile("tiles",1,0,1));
  
  EXPECT_TRUE(gpkg.getTile("tiles",1,1,0));
  EXPECT_TRUE(gpkg.getTile("tiles",1,1,1));

  // 2
  EXPECT_TRUE(gpkg.getTile("tiles",2,0,0));
  EXPECT_TRUE(gpkg.getTile("tiles",2,0,1));
  EXPECT_TRUE(gpkg.getTile("tiles",2,0,2));
  EXPECT_TRUE(gpkg.getTile("tiles",2,0,3));

  EXPECT_TRUE(gpkg.getTile("tiles",2,1,0));
  EXPECT_TRUE(gpkg.getTile("tiles",2,1,1));
  EXPECT_TRUE(gpkg.getTile("tiles",2,1,2));
  EXPECT_TRUE(gpkg.getTile("tiles",2,1,3));

  EXPECT_TRUE(gpkg.getTile("tiles",2,2,0));
  EXPECT_TRUE(gpkg.getTile("tiles",2,2,1));
  EXPECT_TRUE(gpkg.getTile("tiles",2,2,2));
  EXPECT_TRUE(gpkg.getTile("tiles",2,2,3));

  EXPECT_TRUE(gpkg.getTile("tiles",2,3,0));
  EXPECT_TRUE(gpkg.getTile("tiles",2,3,1));
  EXPECT_TRUE(gpkg.getTile("tiles",2,3,2));
  EXPECT_TRUE(gpkg.getTile("tiles",2,3,3));

  EXPECT_TRUE(std::filesystem::remove(fileName));
}