#include <sstream>
#include <iostream>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "layerStyle/DeleteLayerStyleCommand.hpp"
#include "gtest/gtest.h"

TEST(GeoPackageCliTests, DeleteLayerStyleCommand) {
  
  const std::string fileName = "data.gpkg";
  geopackage::GeoPackage gpkg { fileName };
  gpkg.addLayerStyle(geopackage::LayerStyle {
      "", "", "cities", "geom", "cities_default", "", "<sld></sld>", true, "The default cities style", "admin", ""
  });
  EXPECT_TRUE(gpkg.getLayerStyle(1).has_value());
  EXPECT_TRUE(std::filesystem::exists(fileName));

  CLI::App app{"GeoPackageCPP CLI"};  

  Commands commands;
  DeleteLayerStyleCommand cmd{&app};
  commands.add(&cmd);

  int argc = 6;
  char const *argv[6] = {"geopackage-cli", "layerstyle-delete", "-f", "data.gpkg", "-i", "1"};

  app.parse(argc, argv);

  std::istringstream instream;
  std::ostringstream outstream;

  cmd.execute(instream, outstream);

  EXPECT_FALSE(gpkg.getLayerStyle(1).has_value());
  EXPECT_TRUE(std::filesystem::remove(fileName));
}