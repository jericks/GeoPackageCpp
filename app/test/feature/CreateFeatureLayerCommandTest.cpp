#include <sstream>
#include <iostream>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "feature/CreateFeatureLayerCommand.hpp"
#include "gtest/gtest.h"

TEST(GeoPackageCliTests, CreateFeatureLayerCommand) {
  
  const std::string fileName = "data.gpkg";
  geopackage::GeoPackage gpkg { fileName };
  EXPECT_TRUE(std::filesystem::exists(fileName));
  
  CLI::App app{"GeoPackageCPP CLI"};  

  Commands commands;
  CreateFeatureLayerCommand cmd{&app};
  commands.add(&cmd);

  int argc = 22;
  char const *argv[22] = {
    "geopackage-cli", "feature-create", 
    "-f", fileName.c_str(),
    "-n", "cities",
    "-i", "id",
    "-c", "geom",
    "-g", "point",
    "-d", "2D",
    "-s", "4326",
    "-e", "name", "string",
    "-e", "population", "double"
  };

  app.parse(argc, argv);

  std::istringstream instream;
  std::ostringstream outstream;

  cmd.execute(instream, outstream);

  ASSERT_TRUE(gpkg.getContent("cities").has_value());
  ASSERT_TRUE(gpkg.getGeometryColumn("cities").has_value());
  geopackage::Schema schema = gpkg.getSchema("cities");
  ASSERT_EQ("cities", schema.getName());
  EXPECT_EQ("geom", schema.getGeometryField().getName());
  EXPECT_EQ(geopackage::GeometryType::POINT, schema.getGeometryField().getType());
  EXPECT_EQ(4326, schema.getGeometryField().getSrsId());
  EXPECT_EQ(2, schema.getFields().size());
  
  EXPECT_TRUE(std::filesystem::remove(fileName));
}