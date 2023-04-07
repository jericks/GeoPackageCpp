#include <sstream>
#include <iostream>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "geometryColumn/ListGeometryColumnCommand.hpp"
#include "gtest/gtest.h"

TEST(GeoPackageCliTests, ListGeometryColumnCommand) {
  
  const std::string fileName = "data.gpkg";
  geopackage::GeoPackage gpkg { fileName };
  EXPECT_TRUE(std::filesystem::exists(fileName));

  gpkg.addGeometryColumn(geopackage::GeometryColumn{"cities", "geom", geopackage::GeometryType::POINT, 4326, false, false });
  gpkg.addGeometryColumn(geopackage::GeometryColumn{"rivers", "the_geom", geopackage::GeometryType::LINESTRING, 3857, false, true });
  
  CLI::App app{"GeoPackageCPP CLI"};  

  Commands commands;
  ListGeometryColumnCommand cmd{&app};
  commands.add(&cmd);

  int argc = 4;
  char const *argv[4] = {"geopackage-cli", "geometrycolumn-list", "-f", "data.gpkg"};

  app.parse(argc, argv);

  std::istringstream instream;
  std::ostringstream outstream;

  cmd.execute(instream, outstream);

  std::string result = outstream.str();
  
  ASSERT_NE(std::string::npos, result.find("cities"));
  ASSERT_NE(std::string::npos, result.find("rivers"));

  EXPECT_TRUE(std::filesystem::remove(fileName));
}