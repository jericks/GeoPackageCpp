#include <sstream>
#include <iostream>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "geometryColumn/DeleteGeometryColumnCommand.hpp"
#include "gtest/gtest.h"

TEST(GeoPackageCliTests, DeleteGeometryColumnCommand) {
  
  const std::string fileName = "data.gpkg";
  geopackage::GeoPackage gpkg { fileName };
  EXPECT_TRUE(std::filesystem::exists(fileName));
  
  gpkg.addGeometryColumn(geopackage::GeometryColumn{"cities", "geom", geopackage::GeometryType::POINT, 4326, false, false });
  
  CLI::App app{"GeoPackageCPP CLI"};  

  Commands commands;
  DeleteGeometryColumnCommand cmd{&app};
  commands.add(&cmd);

  int argc = 6;
  char const *argv[6] = {"geopackage-cli", "geometrycolumn-delete", "-f", "data.gpkg", "-n", "cities"};

  app.parse(argc, argv);

  std::istringstream instream;
  std::ostringstream outstream;
  cmd.execute(instream, outstream);

  EXPECT_FALSE(gpkg.getGeometryColumn("cities").has_value());
  EXPECT_TRUE(std::filesystem::remove(fileName));
}