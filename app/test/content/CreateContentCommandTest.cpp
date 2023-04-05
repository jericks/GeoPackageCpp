#include <sstream>
#include <iostream>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "content/CreateContentCommand.hpp"
#include "gtest/gtest.h"

TEST(GeoPackageCliTests, CreateContentCommand) {
  
  const std::string fileName = "data.gpkg";
  geopackage::GeoPackage gpkg { fileName };
  EXPECT_TRUE(std::filesystem::exists(fileName));
  EXPECT_FALSE(gpkg.getContent("cities").has_value());

  CLI::App app{"GeoPackageCPP CLI"};  

  Commands commands;
  CreateContentCommand cmd{&app};
  commands.add(&cmd);

  int argc = 16;
  char const *argv[16] = {
    "geopackage-cli", "content-create", 
    "-f", "data.gpkg", 
    "-n", "cities",
    "-t", "feature",
    "-i", "cities",
    "-d", "A cities layer",
    "-b", "-180,-90,180,90",
    "-s", "4326"
  };

  app.parse(argc, argv);

  std::istringstream instream;
  std::ostringstream outstream;

  cmd.execute(instream, outstream);

  EXPECT_TRUE(gpkg.getContent("cities").has_value());

  EXPECT_TRUE(std::filesystem::remove(fileName));
}