#include <sstream>
#include <iostream>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "feature/AddFeatureCommand.hpp"
#include "feature/UpdateFeatureCommand.hpp"
#include "gtest/gtest.h"

TEST(GeoPackageCliTests, UpdateFeatureCommand) {
  
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
  AddFeatureCommand addCmd{&app};
  commands.add(&addCmd);
  UpdateFeatureCommand updateCmd{&app};
  commands.add(&updateCmd);

  int addArgc = 14;
  char const *addArgv[14] = {
    "geopackage-cli", "feature-add", 
    "-f", "data.gpkg", 
    "-n", "cities",
    "-g", "POINT(30 30)",
    "-v", "name", "Seattle",
    "-v", "population", "100"
  };

  app.parse(addArgc, addArgv);

  std::istringstream addinstream;
  std::ostringstream addoutstream;

  addCmd.execute(addinstream, addoutstream);
  ASSERT_EQ(1, gpkg.countFeatures("cities"));

  int argc = 16;
  char const *argv[16] = {
    "geopackage-cli", "feature-update", 
    "-f", "data.gpkg", 
    "-n", "cities",
    "-i", "1",
    "-g", "POINT(40 40)",
    "-v", "name", "Tacoma",
    "-v", "population", "90"
  };

  app.parse(argc, argv);

  std::istringstream instream;
  std::ostringstream outstream;

  updateCmd.execute(instream, outstream);
  ASSERT_EQ(1, gpkg.countFeatures("cities"));

  auto feature = gpkg.getFeature("cities", 1);
  ASSERT_EQ(1, feature->getId());
  ASSERT_EQ("POINT (40 40)", feature->getGeometry()->wkt());
  ASSERT_EQ("Tacoma", std::any_cast<std::string>(feature->getAttributes()["name"]));
  
  EXPECT_TRUE(std::filesystem::remove(fileName));
}