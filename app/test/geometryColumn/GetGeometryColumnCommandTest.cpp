#include <sstream>
#include <iostream>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "geometryColumn/GetGeometryColumnCommand.hpp"
#include "gtest/gtest.h"

TEST(GeoPackageCliTests, GetGeometryColumnCommand) {
  
  const std::string fileName = "data.gpkg";
  geopackage::GeoPackage gpkg { fileName };
  EXPECT_TRUE(std::filesystem::exists(fileName));

  gpkg.addGeometryColumn(geopackage::GeometryColumn{"cities", "geom", geopackage::GeometryType::POINT, 4326, false, false });
  
  CLI::App app{"GeoPackageCPP CLI"};  

  Commands commands;
  GetGeometryColumnCommand cmd{&app};
  commands.add(&cmd);

  int argc = 6;
  char const *argv[6] = {"geopackage-cli", "geometrycolumn-get", "-f", "data.gpkg", "-n", "cities"};

  app.parse(argc, argv);

  std::istringstream instream;
  std::ostringstream outstream;

  cmd.execute(instream, outstream);

  std::string result = outstream.str();
  ASSERT_NE(std::string::npos, result.find("Name: cities"));
  ASSERT_NE(std::string::npos, result.find("Column: geom"));
  ASSERT_NE(std::string::npos, result.find("Geometry Type: Point"));
  ASSERT_NE(std::string::npos, result.find("SRS ID: 4326"));
  ASSERT_NE(std::string::npos, result.find("Has Z: false"));
  ASSERT_NE(std::string::npos, result.find("Has M: false"));

  EXPECT_TRUE(std::filesystem::remove(fileName));
}