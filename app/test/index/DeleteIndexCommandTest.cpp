#include <sstream>
#include <iostream>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "feature/RandomFeaturesCommand.hpp"
#include "index/CreateIndexCommand.hpp"
#include "index/DeleteIndexCommand.hpp"
#include "gtest/gtest.h"

TEST(GeoPackageCliTests, DeleteIndexCommand) {
  
  const std::string fileName = "data.gpkg";
  geopackage::GeoPackage gpkg { fileName };
  EXPECT_TRUE(std::filesystem::exists(fileName));
  
  CLI::App app{"GeoPackageCPP CLI"};  

  Commands commands;
  RandomFeaturesCommand randomCmd{&app};
  commands.add(&randomCmd);
  CreateIndexCommand createIndexCmd{&app};
  commands.add(&createIndexCmd);
  DeleteIndexCommand deleteIndexCmd{&app};
  commands.add(&deleteIndexCmd);

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
  
  int createIndexArgc = 6;
  char const *createIndexArgv[6] = {
    "geopackage-cli", "index-create", 
    "-f", "data.gpkg",
    "-n", "points"
  };
  app.parse(createIndexArgc, createIndexArgv);

  std::istringstream createIndexInstream;
  std::ostringstream createIndexOutstream;

  createIndexCmd.execute(createIndexInstream, createIndexOutstream);

  int deleteIndexArgc = 6;
  char const *deleteIndexArgv[6] = {
    "geopackage-cli", "index-delete", 
    "-f", "data.gpkg",
    "-n", "points"
  };
  app.parse(deleteIndexArgc, deleteIndexArgv);

  std::istringstream deleteIndexInstream;
  std::ostringstream deleteIndexOutstream;

  deleteIndexCmd.execute(deleteIndexInstream, deleteIndexOutstream);

  EXPECT_TRUE(std::filesystem::remove(fileName));
}