#include <sstream>
#include <iostream>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "layerStyle/GetLayerStyleCommand.hpp"
#include "gtest/gtest.h"

TEST(GeoPackageCliTests, GetLayerStyleCommand) {
  
  const std::string fileName = "data.gpkg";
  geopackage::GeoPackage gpkg { fileName };
  gpkg.addLayerStyle(geopackage::LayerStyle {
      "", "", "cities", "geom", "cities_default", "", "<sld></sld>", true, "The default cities style", "admin", ""
  });
  gpkg.addLayerStyle(geopackage::LayerStyle {
      "", "", "cities", "geom", "cities_red", "", R"(<?xml version="1.0" encoding="UTF-8"?><sld:StyledLayerDescriptor xmlns:sld="http://www.opengis.net/sld" xmlns="http://www.opengis.net/sld" xmlns:gml="http://www.opengis.net/gml" xmlns:ogc="http://www.opengis.net/ogc" version="1.0.0">
  <sld:UserLayer>
    <sld:LayerFeatureConstraints>
      <sld:FeatureTypeConstraint/>
    </sld:LayerFeatureConstraints>
    <sld:UserStyle>
      <sld:Name>Default Styler</sld:Name>
      <sld:FeatureTypeStyle>
        <sld:Name>name</sld:Name>
        <sld:Rule>
          <sld:PolygonSymbolizer>
            <sld:Fill>
              <sld:CssParameter name="fill">#ffffff</sld:CssParameter>
            </sld:Fill>
          </sld:PolygonSymbolizer>
          <sld:LineSymbolizer>
            <sld:Stroke>
              <sld:CssParameter name="stroke-width">0.5</sld:CssParameter>
            </sld:Stroke>
          </sld:LineSymbolizer>
        </sld:Rule>
      </sld:FeatureTypeStyle>
    </sld:UserStyle>
  </sld:UserLayer>
</sld:StyledLayerDescriptor>)", true, "The red cities style", "admin", ""
  });
  gpkg.addLayerStyle(geopackage::LayerStyle {
      "", "", "rivers", "geom", "blue_rivers", "", "<sld></sld>", true, "The default rivers style", "admin", ""
  });
  EXPECT_TRUE(std::filesystem::exists(fileName));

  CLI::App app{"GeoPackageCPP CLI"};  

  Commands commands;
  GetLayerStyleCommand cmd{&app};
  commands.add(&cmd);

  int argc = 6;
  char const *argv[6] = {"geopackage-cli", "layerstyle-get", "-f", "data.gpkg", "-i", "2"};

  app.parse(argc, argv);

  std::istringstream instream;
  std::ostringstream outstream;

  cmd.execute(instream, outstream);

  std::string result = outstream.str();
  ASSERT_NE(std::string::npos, result.find("cities_red"));
  ASSERT_NE(std::string::npos, result.find("<sld:StyledLayerDescriptor"));

  EXPECT_TRUE(std::filesystem::remove(fileName));
}