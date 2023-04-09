#include <sstream>
#include <iostream>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "geometryColumn/CreateGeometryColumnCommand.hpp"
#include "gtest/gtest.h"

TEST(GeoPackageCliTests, CreateGeometryColumnCommand) {
  
  const std::string fileName = "data.gpkg";
  geopackage::GeoPackage gpkg { fileName };
  EXPECT_TRUE(std::filesystem::exists(fileName));
  EXPECT_FALSE(gpkg.getGeometryColumn("cities").has_value());

  CLI::App app{"GeoPackageCPP CLI"};  

  Commands commands;
  CreateGeometryColumnCommand cmd{&app};
  commands.add(&cmd);

  int argc = 16;
  char const *argv[16] = {
    "geopackage-cli", "geometrycolumn-create", 
    "-f", "data.gpkg", 
    "-n", "cities",
    "-c", "geometry",
    "-g", "Point",
    "-s", "4326",
    "-z", "true",
    "-m", "false"
  };

  app.parse(argc, argv);

  std::istringstream instream;
  std::ostringstream outstream;

  cmd.execute(instream, outstream);

  EXPECT_TRUE(gpkg.getGeometryColumn("cities").has_value());

  EXPECT_TRUE(std::filesystem::remove(fileName));
}