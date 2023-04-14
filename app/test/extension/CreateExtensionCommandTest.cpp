#include <sstream>
#include <iostream>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "extension/CreateExtensionCommand.hpp"
#include "gtest/gtest.h"

TEST(GeoPackageCliTests, CreateExtensionCommand) {
  
  const std::string fileName = "data.gpkg";
  geopackage::GeoPackage gpkg { fileName };
  EXPECT_TRUE(std::filesystem::exists(fileName));
  EXPECT_FALSE(gpkg.getExtension("cities").has_value());

  CLI::App app{"GeoPackageCPP CLI"};  

  Commands commands;
  CreateExtensionCommand cmd{&app};
  commands.add(&cmd);

  int argc = 14;
  char const *argv[14] = {
    "geopackage-cli", "extension-create", 
    "-f", "data.gpkg", 
    "-n", "index",
    "-c", "r_tree",
    "-e", "Spatial Index",
    "-d", "A R-Tree Spatial Index",
    "-s", "read-write"
  };

  app.parse(argc, argv);

  std::istringstream instream;
  std::ostringstream outstream;

  cmd.execute(instream, outstream);

  EXPECT_TRUE(gpkg.getExtension("Spatial Index").has_value());

  EXPECT_TRUE(std::filesystem::remove(fileName));
}