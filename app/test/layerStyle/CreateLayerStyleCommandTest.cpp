#include <sstream>
#include <iostream>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "layerStyle/CreateLayerStyleCommand.hpp"
#include "gtest/gtest.h"

TEST(GeoPackageCliTests, CreateLayerStyleCommand) {
  
  const std::string fileName = "data.gpkg";
  geopackage::GeoPackage gpkg { fileName };
  EXPECT_TRUE(std::filesystem::exists(fileName));

  CLI::App app{"GeoPackageCPP CLI"};  

  Commands commands;
  CreateLayerStyleCommand cmd{&app};
  commands.add(&cmd);

  int argc = 26;
  char const *argv[26] = {
    "geopackage-cli", "layerstyle-create", "-f", "data.gpkg", 
    "-c", "", "-a", "", "-n", "cities", "-g", "geom", 
    "-t", "cities_default", "-q", "", "-s", "<sld></sld>", "-l", "true", 
    "-d", "The default cities style", "-o", "admin", "-u", ""};

  app.parse(argc, argv);

  std::istringstream instream;
  std::ostringstream outstream;

  cmd.execute(instream, outstream);

  auto layerStyle = gpkg.getLayerStyle(1);
  EXPECT_TRUE(layerStyle.has_value());
  EXPECT_EQ("cities", layerStyle->getTableName());
  EXPECT_EQ("cities_default", layerStyle->getStyleName());

  EXPECT_TRUE(std::filesystem::remove(fileName));
}