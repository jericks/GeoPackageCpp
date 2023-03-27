#include <sstream>
#include <iostream>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "DeleteSpatialRefCommand.hpp"
#include "gtest/gtest.h"

TEST(GeoPackageCliTests, DeleteSpatialRefCommand) {
  
  const std::string fileName = "data.gpkg";
  geopackage::GeoPackage gpkg { fileName };
  gpkg.insertDefaultSpatialRefs();
  EXPECT_TRUE(std::filesystem::exists(fileName));
  EXPECT_TRUE(gpkg.getSpatialRef(4326).has_value());
  
  CLI::App app{"GeoPackageCPP CLI"};  

  Commands commands;
  DeleteSpatialRefCommand cmd{&app};
  commands.add(&cmd);

  int argc = 6;
  char const *argv[6] = {"geopackage-cli", "spatialref-delete", "-f", "data.gpkg", "-s", "4326"};

  app.parse(argc, argv);

  std::istringstream instream;
  std::ostringstream outstream;

  cmd.execute(instream, outstream);

  EXPECT_FALSE(gpkg.getSpatialRef(4326).has_value());
  EXPECT_TRUE(std::filesystem::remove(fileName));
}