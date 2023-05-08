#include <sstream>
#include <iostream>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "feature/ListFeatureLayersCommand.hpp"
#include "gtest/gtest.h"

TEST(GeoPackageCliTests, ListFeatureLayersCommand) {
  
  const std::string fileName = "data.gpkg";
  geopackage::GeoPackage gpkg { fileName };
  EXPECT_TRUE(std::filesystem::exists(fileName));
  
  gpkg.addContent(geopackage::Content{"cities", geopackage::DataType::FEATURES, "cities", "A Layer of cities", "2022-01-29T18:38:34.649Z", geopackage::Bounds{-180,-90,180,90}, 4326});
  gpkg.addContent(geopackage::Content{"countries", geopackage::DataType::FEATURES, "countries", "A Layer of countries", "2022-01-29T18:38:34.649Z", geopackage::Bounds{-180,-90,180,90}, 4326});
  gpkg.addContent(geopackage::Content{"rivers", geopackage::DataType::FEATURES, "rivers", "A Layer of rivers", "2022-01-29T18:38:34.649Z", geopackage::Bounds{-180,-90,180,90}, 4326});
  gpkg.addContent(geopackage::Content{"world_geo", geopackage::DataType::TILES, "world_geo", "A set of tiles", "2022-01-29T18:38:34.649Z", geopackage::Bounds{-180,-90,180,90}, 4326});
  gpkg.addContent(geopackage::Content{"world_merc", geopackage::DataType::TILES, "world_merc", "A set of tiles", "2022-01-29T18:38:34.649Z", geopackage::Bounds{-180,-90,180,90}, 4326});
  
  CLI::App app{"GeoPackageCPP CLI"};  

  Commands commands;
  ListFeatureLayersCommand cmd{&app};
  commands.add(&cmd);

  int argc = 4;
  char const *argv[4] = {
    "geopackage-cli", "feature-list", 
    "-f", "data.gpkg"
  };

  app.parse(argc, argv);

  std::istringstream instream;
  std::ostringstream outstream;

  cmd.execute(instream, outstream);

  std::string result = outstream.str();
  ASSERT_NE(std::string::npos, result.find("cities"));
  ASSERT_NE(std::string::npos, result.find("rivers"));
  ASSERT_NE(std::string::npos, result.find("countries"));
  ASSERT_EQ(std::string::npos, result.find("world_geo"));
  ASSERT_EQ(std::string::npos, result.find("world_merc"));
  
  EXPECT_TRUE(std::filesystem::remove(fileName));
}