#include <sstream>
#include <iostream>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "tileMatrix/CreateTileMatrixCommand.hpp"
#include "gtest/gtest.h"

TEST(GeoPackageCliTests, CreateTileMatrixCommand) {
  
  const std::string fileName = "data.gpkg";
  geopackage::GeoPackage gpkg { fileName };
  EXPECT_TRUE(std::filesystem::exists(fileName));
  
  CLI::App app{"GeoPackageCPP CLI"};  

  Commands commands;
  CreateTileMatrixCommand cmd{&app};
  commands.add(&cmd);

  int argc = 14;
  char const *argv[14] = {
    "geopackage-cli", "tilematrix-create", 
    "-f", "data.gpkg", 
    "-n", "world",
    "-z", "1",
    "-m", "2,1",
    "-t", "256,256",
    "-p", "0.703125,0.703125"
  };

  app.parse(argc, argv);

  std::istringstream instream;
  std::ostringstream outstream;

  cmd.execute(instream, outstream);

  std::string result = outstream.str();

  EXPECT_TRUE(gpkg.getTileMatrix("world", 1).has_value());
  
  EXPECT_TRUE(std::filesystem::remove(fileName));
}