#include <sstream>
#include <iostream>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "feature/ListFeatureCommand.hpp"
#include "gtest/gtest.h"

TEST(GeoPackageCliTests, ListFeatureCommand) {
  
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

  gpkg.addFeature("cities", geopackage::Feature{
      std::make_unique<geopackage::Point>(-122, 47),
      std::map<std::string, std::any> {{"population", 737000}, {"name", std::string{"One"}}}
  });
  gpkg.addFeature("cities", geopackage::Feature{
      std::make_unique<geopackage::Point>(-123, 48),
      std::map<std::string, std::any> {{"population", 123}, {"name", std::string{"Two"}}}
  });

  CLI::App app{"GeoPackageCPP CLI"};  

  Commands commands;
  ListFeatureCommand cmd{&app};
  commands.add(&cmd);

  int argc = 6;
  char const *argv[6] = {
    "geopackage-cli", "features", 
    "-f", "data.gpkg", 
    "-n", "cities"
  };

  app.parse(argc, argv);

  std::istringstream instream;
  std::ostringstream outstream;

  cmd.execute(instream, outstream);

  std::string result = outstream.str();
  ASSERT_NE(std::string::npos, result.find("\"geometry\",\"id\",\"name\",\"population\""));
  ASSERT_NE(std::string::npos, result.find("\"POINT (-122 47)\",\"1\",\"One\",\"737000\""));
  ASSERT_NE(std::string::npos, result.find("\"POINT (-123 48)\",\"2\",\"Two\",\"123\""));
  
  EXPECT_TRUE(std::filesystem::remove(fileName));
}