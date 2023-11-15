#include <sstream>
#include <iostream>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "layerStyle/LoadLayerStyleCommand.hpp"
#include "gtest/gtest.h"

TEST(GeoPackageCliTests, LoadLayerStyleCommand) {
  
  const std::string fileName = "data.gpkg";
  geopackage::GeoPackage gpkg { fileName };
  gpkg.addLayerStyle(geopackage::LayerStyle {
      "", "", "cities", "geom", "cities_default", "", "<sld></sld>", true, "The default cities style", "admin", ""
  });
  EXPECT_TRUE(std::filesystem::exists(fileName));

  CLI::App app{"GeoPackageCPP CLI"};  

  Commands commands;
  LoadLayerStyleCommand cmd{&app};
  commands.add(&cmd);

  int argc = 8;
  char const *argv[8] = {"geopackage-cli", "layerstyle-load", "-f", "data.gpkg", "-i", "1", "-s", "../../../data/style.sld"};

  app.parse(argc, argv);

  std::istringstream instream;
  std::ostringstream outstream;

  cmd.execute(instream, outstream);

  auto layerStyle = gpkg.getLayerStyle(1);
  ASSERT_NE(std::string::npos, layerStyle->getStyleSLD().find("<sld:StyledLayerDescriptor"));
  EXPECT_TRUE(std::filesystem::remove(fileName));
}