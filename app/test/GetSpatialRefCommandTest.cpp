#include <sstream>
#include <iostream>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "GetSpatialRefCommand.hpp"
#include "gtest/gtest.h"

TEST(GeoPackageCliTests, GetSpatialRefCommand) {
  
  const std::string fileName = "data.gpkg";
  geopackage::GeoPackage gpkg { fileName };
  gpkg.insertDefaultSpatialRefs();
  EXPECT_TRUE(std::filesystem::exists(fileName));
  
  CLI::App app{"GeoPackageCPP CLI"};  

  Commands commands;
  GetSpatialRefCommand cmd{&app};
  commands.add(&cmd);

  int argc = 6;
  char const *argv[6] = {"geopackage-cli", "spatialref-get", "-f", "data.gpkg", "-s", "4326"};

  app.parse(argc, argv);

  std::istringstream instream;
  std::ostringstream outstream;

  cmd.execute(instream, outstream);

  std::string result = outstream.str();
  ASSERT_NE(std::string::npos, result.find("4326"));


  EXPECT_TRUE(std::filesystem::remove(fileName));
}