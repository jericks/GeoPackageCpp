#include <sstream>
#include <iostream>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "layerStyle/ListLayerStyleCommand.hpp"
#include "gtest/gtest.h"

TEST(GeoPackageCliTests, ListLayerStyleCommand) {
  
  const std::string fileName = "data.gpkg";
  geopackage::GeoPackage gpkg { fileName };
  gpkg.addLayerStyle(geopackage::LayerStyle {
      "", "", "cities", "geom", "cities_default", "", "<sld></sld>", true, "The default cities style", "admin", ""
  });
  gpkg.addLayerStyle(geopackage::LayerStyle {
      "", "", "cities", "geom", "cities_red", "", "<sld></sld>", true, "The red cities style", "admin", ""
  });
  gpkg.addLayerStyle(geopackage::LayerStyle {
      "", "", "rivers", "geom", "blue_rivers", "", "<sld></sld>", true, "The default rivers style", "admin", ""
  });
  EXPECT_TRUE(std::filesystem::exists(fileName));

  CLI::App app{"GeoPackageCPP CLI"};  

  Commands commands;
  ListLayerStyleCommand cmd{&app};
  commands.add(&cmd);

  int argc = 4;
  char const *argv[4] = {"geopackage-cli", "layerstyle-list", "-f", "data.gpkg"};

  app.parse(argc, argv);

  std::istringstream instream;
  std::ostringstream outstream;

  cmd.execute(instream, outstream);

  std::string result = outstream.str();
  ASSERT_NE(std::string::npos, result.find("cities_default"));
  ASSERT_NE(std::string::npos, result.find("blue_rivers"));

  EXPECT_TRUE(std::filesystem::remove(fileName));
}