#include <sstream>
#include <iostream>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "CreateSpatialRefCommand.hpp"
#include "gtest/gtest.h"

TEST(GeoPackageCliTests, CreateSpatialRefCommand) {
  
  const std::string fileName = "data.gpkg";
  EXPECT_TRUE(std::filesystem::exists(fileName));
  
  CLI::App app{"GeoPackageCPP CLI"};  

  Commands commands;
  CreateSpatialRefCommand cmd{&app};
  commands.add(&cmd);

  int argc = 16;
  char const *argv[16] = {
    "geopackage-cli", "spatialref-create", 
    "-f", "data.gpkg", 
    "-n", "WAStatePlaneSouth",
    "-s", "2927",
    "-o", "EPSG",
    "-i", "2927",
    "-c", "WashingtonStatePlaneSouth",
    "-d", "2927"
  };

  app.parse(argc, argv);

  std::istringstream instream;
  std::ostringstream outstream;

  cmd.execute(instream, outstream);

  std::string result = outstream.str();

  geopackage::GeoPackage gpkg { fileName };
  EXPECT_TRUE(gpkg.getSpatialRef(2927).has_value());
  
  EXPECT_TRUE(std::filesystem::remove(fileName));
}