#include <sstream>
#include <iostream>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "tile/InfoTileCommand.hpp"
#include "gtest/gtest.h"

TEST(GeoPackageCliTests, InfoTileCommand) {
  
  const std::string fileName = "data.gpkg";
  geopackage::GeoPackage gpkg { fileName };
  EXPECT_TRUE(std::filesystem::exists(fileName));
  
  gpkg.createGlobalMercatorTileLayer("world", 256, 19);
  gpkg.loadTilesFromDirectory("world", "../../../data/tms");

  CLI::App app{"GeoPackageCPP CLI"};  

  Commands commands;
  InfoTileCommand cmd{&app};
  commands.add(&cmd);

  int argc = 6;
  char const *argv[6] = {
    "geopackage-cli", "tile-info", 
    "-f", "data.gpkg", 
    "-n", "world"
  };

  app.parse(argc, argv);

  std::istringstream instream;
  std::ostringstream outstream;

  cmd.execute(instream, outstream);

  std::string result = outstream.str();
  ASSERT_NE(std::string::npos, result.find("Information"));
  ASSERT_NE(std::string::npos, result.find("Name: world"));
  ASSERT_NE(std::string::npos, result.find("Tiles"));
  ASSERT_NE(std::string::npos, result.find("0 = 1"));
  ASSERT_NE(std::string::npos, result.find("1 = 4"));
  ASSERT_NE(std::string::npos, result.find("2 = 16"));
  
  EXPECT_TRUE(std::filesystem::remove(fileName));
}