#include <sstream>
#include <iostream>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "tileMatrixSet/CreateTileMatrixSetCommand.hpp"
#include "gtest/gtest.h"

TEST(GeoPackageCliTests, CreateTileMatrixSetCommand) {
  
  const std::string fileName = "data.gpkg";
  geopackage::GeoPackage gpkg { fileName };
  EXPECT_TRUE(std::filesystem::exists(fileName));
  
  CLI::App app{"GeoPackageCPP CLI"};  

  Commands commands;
  CreateTileMatrixSetCommand cmd{&app};
  commands.add(&cmd);

  int argc = 10;
  char const *argv[10] = {
    "geopackage-cli", "tilematrixset-create", 
    "-f", "data.gpkg", 
    "-n", "world",
    "-s", "4326",
    "-b", "-180.-90,180,90"
  };

  app.parse(argc, argv);

  std::istringstream instream;
  std::ostringstream outstream;

  cmd.execute(instream, outstream);

  std::string result = outstream.str();

  EXPECT_TRUE(gpkg.getTileMatrixSet("world").has_value());
  
  EXPECT_TRUE(std::filesystem::remove(fileName));
}