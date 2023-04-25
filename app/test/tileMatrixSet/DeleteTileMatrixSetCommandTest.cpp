#include <sstream>
#include <iostream>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "tileMatrixSet/DeleteTileMatrixSetCommand.hpp"
#include "gtest/gtest.h"

TEST(GeoPackageCliTests, DeleteTileMatrixSetCommand) {
  
  const std::string fileName = "data.gpkg";
  geopackage::GeoPackage gpkg { fileName };
  EXPECT_TRUE(std::filesystem::exists(fileName));
  
  gpkg.addTileMatrixSet(geopackage::TileMatrixSet{"basemap", 4326, geopackage::Bounds{-180,-90,180,90}});
  gpkg.addTileMatrixSet(geopackage::TileMatrixSet{"tiles", 3857, geopackage::Bounds{-20037508.3427892,-20037508.3427892,20037508.3427892,0037508.3427892}});

  CLI::App app{"GeoPackageCPP CLI"};  

  Commands commands;
  DeleteTileMatrixSetCommand cmd{&app};
  commands.add(&cmd);

  int argc = 6;
  char const *argv[6] = {"geopackage-cli", "tilematrixset-delete", "-f", "data.gpkg", "-n", "tiles"};

  app.parse(argc, argv);

  std::istringstream instream;
  std::ostringstream outstream;

  cmd.execute(instream, outstream);

  EXPECT_FALSE(gpkg.getTileMatrixSet("tiles").has_value());
  EXPECT_TRUE(gpkg.getTileMatrixSet("basemap").has_value());

  EXPECT_TRUE(std::filesystem::remove(fileName));
}