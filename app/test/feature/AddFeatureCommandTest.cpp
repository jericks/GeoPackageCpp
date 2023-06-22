#include <sstream>
#include <iostream>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "feature/AddFeatureCommand.hpp"
#include "gtest/gtest.h"

TEST(GeoPackageCliTests, AddFeatureCommand) {
  
  const std::string fileName = "data.gpkg";
  geopackage::GeoPackage gpkg { fileName };
  EXPECT_TRUE(std::filesystem::exists(fileName));
  
  geopackage::Schema schema{
      "cities",
      "id",
      geopackage::GeometryField{"geometry", geopackage::GeometryType::POINT, 4326},
      std::vector{
          geopackage::Field{"name", geopackage::FieldType::String},
          geopackage::Field{"population", geopackage::FieldType::Double}
      }
  };
  geopackage::Bounds bounds = geopackage::Bounds::getGeodeticBounds();
  gpkg.createFeatureLayer(schema, bounds);

  CLI::App app{"GeoPackageCPP CLI"};  

  Commands commands;
  AddFeatureCommand cmd{&app};
  commands.add(&cmd);

  int argc = 14;
  char const *argv[14] = {
    "geopackage-cli", "feature-add", 
    "-f", "data.gpkg", 
    "-n", "cities",
    "-g", "POINT(30 30)",
    "-v", "name", "Seattle",
    "-v", "population", "100"
  };

  app.parse(argc, argv);

  std::istringstream instream;
  std::ostringstream outstream;

  cmd.execute(instream, outstream);
  ASSERT_EQ(1, gpkg.countFeatures("cities"));
  
  EXPECT_TRUE(std::filesystem::remove(fileName));
}