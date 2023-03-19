#include <sstream>
#include <iostream>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "ListSpatialRefCommand.hpp"
#include "gtest/gtest.h"

TEST(GeoPackageCliTests, ListSpatialRefCommand) {
  
  const std::string fileName = "data.gpkg";
  geopackage::GeoPackage gpkg { fileName };
  gpkg.insertDefaultSpatialRefs();
  EXPECT_TRUE(std::filesystem::exists(fileName));
  
  CLI::App app{"GeoPackageCPP CLI"};  

  Commands commands;
  ListSpatialRefCommand cmd{&app};
  commands.add(&cmd);

  int argc = 4;
  char const *argv[4] = {"geopackage-cli", "spatialref-list", "-f", "data.gpkg"};

  app.parse(argc, argv);

  std::istringstream instream;
  std::ostringstream outstream;

  cmd.execute(instream, outstream);

  std::string result = outstream.str();
  ASSERT_NE(std::string::npos, result.find("3857"));
  ASSERT_NE(std::string::npos, result.find("4326"));


  EXPECT_TRUE(std::filesystem::remove(fileName));
}