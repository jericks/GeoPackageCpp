#include <sstream>
#include <iostream>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "feature/InfoFeatureCommand.hpp"
#include "gtest/gtest.h"

TEST(GeoPackageCliTests, InfoFeatureCommand) {
  
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
  InfoFeatureCommand cmd{&app};
  commands.add(&cmd);

  int argc = 6;
  char const *argv[6] = {
    "geopackage-cli", "feature-info", 
    "-f", "data.gpkg", 
    "-n", "cities"
  };

  app.parse(argc, argv);

  std::istringstream instream;
  std::ostringstream outstream;

  cmd.execute(instream, outstream);

  std::string result = outstream.str();
  ASSERT_NE(std::string::npos, result.find("Information"));
  ASSERT_NE(std::string::npos, result.find("Name: cities"));
  
  EXPECT_TRUE(std::filesystem::remove(fileName));
}