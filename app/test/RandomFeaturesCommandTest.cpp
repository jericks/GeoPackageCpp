#include <sstream>
#include <iostream>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "RandomFeaturesCommand.hpp"
#include "gtest/gtest.h"

TEST(GeoPackageCliTests, RandomFeaturesCommand) {
  
  
  CLI::App app{"GeoPackageCPP CLI"};  

  Commands commands;
  RandomFeaturesCommand cmd{&app};
  commands.add(&cmd);

  const std::string fileName = "data.gpkg";
  int argc = 8;
  char const *argv[8] = {"geopackage-cli", "random-features", "-f", fileName.c_str(), "-l", "points", "-n", "10"};

  app.parse(argc, argv);

  std::istringstream instream;
  std::ostringstream outstream;

  cmd.execute(instream, outstream);

  std::string result = outstream.str();
  
  
  geopackage::GeoPackage gpkg { fileName };
  EXPECT_TRUE(std::filesystem::exists(fileName));
  EXPECT_EQ(10, gpkg.countFeatures("points"));

  EXPECT_TRUE(std::filesystem::remove(fileName));
}