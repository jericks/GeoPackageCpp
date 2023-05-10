#include <sstream>
#include <iostream>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "feature/RandomFeaturesCommand.hpp"
#include "feature/CountFeaturesCommand.hpp"
#include "gtest/gtest.h"

TEST(GeoPackageCliTests, CountFeaturesCommand) {
  
  const std::string fileName = "data.gpkg";
  geopackage::GeoPackage gpkg { fileName };
  EXPECT_TRUE(std::filesystem::exists(fileName));
  
  CLI::App app{"GeoPackageCPP CLI"};  

  Commands commands;
  RandomFeaturesCommand randomCmd{&app};
  commands.add(&randomCmd);
  CountFeaturesCommand cmd{&app};
  commands.add(&cmd);

  int randomArgc = 8;
  char const *randomArgv[8] = {
    "geopackage-cli", "random-features",
    "-f", "data.gpkg",
    "-l", "points", 
    "-n", "10"
  };
  app.parse(randomArgc, randomArgv);

  std::istringstream randomInstream;
  std::ostringstream randomOutstream;

  randomCmd.execute(randomInstream, randomOutstream);
  EXPECT_EQ(10, gpkg.countFeatures("points"));
  
  int argc = 6;
  char const *argv[6] = {
    "geopackage-cli", "feature-count", 
    "-f", "data.gpkg",
    "-n", "points"
  };
  app.parse(argc, argv);

  std::istringstream instream;
  std::ostringstream outstream;

  cmd.execute(instream, outstream);

  std::string result = outstream.str();
  ASSERT_NE(std::string::npos, result.find("10"));
  
  EXPECT_TRUE(std::filesystem::remove(fileName));
}