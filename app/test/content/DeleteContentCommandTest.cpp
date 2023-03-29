#include <sstream>
#include <iostream>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "content/DeleteContentCommand.hpp"
#include "gtest/gtest.h"

TEST(GeoPackageCliTests, DeleteContentCommand) {
  
  const std::string fileName = "data.gpkg";
  geopackage::GeoPackage gpkg { fileName };
  EXPECT_TRUE(std::filesystem::exists(fileName));
  
  gpkg.addContent(geopackage::Content{"cities", geopackage::DataType::FEATURES, "cities", "A Layer of cities", "2022-01-29T18:38:34.649Z", geopackage::Bounds{-180,-90,180,90}, 4326});
  gpkg.addContent(geopackage::Content{"tiles", geopackage::DataType::TILES, "tiles", "A set of tiles", "2022-01-29T18:38:34.649Z", geopackage::Bounds{-180,-90,180,90}, 4326});
  
  CLI::App app{"GeoPackageCPP CLI"};  

  Commands commands;
  DeleteContentCommand cmd{&app};
  commands.add(&cmd);

  int argc = 6;
  char const *argv[6] = {"geopackage-cli", "content-delete", "-f", "data.gpkg", "-n", "cities"};

  app.parse(argc, argv);

  std::istringstream instream;
  std::ostringstream outstream;

  cmd.execute(instream, outstream);

  EXPECT_FALSE(gpkg.getContent("cities").has_value());
  EXPECT_TRUE(gpkg.getContent("tiles").has_value());
  EXPECT_TRUE(std::filesystem::remove(fileName));
}