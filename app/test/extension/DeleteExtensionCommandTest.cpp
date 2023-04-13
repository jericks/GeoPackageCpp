#include <sstream>
#include <iostream>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "extension/DeleteExtensionCommand.hpp"
#include "gtest/gtest.h"

TEST(GeoPackageCliTests, DeleteExtensionCommand) {
  
  const std::string fileName = "data.gpkg";
  geopackage::GeoPackage gpkg { fileName };
  EXPECT_TRUE(std::filesystem::exists(fileName));
  
  gpkg.addExtension(geopackage::Extension{"point_index", "index", "Point Index", "R-TREE", geopackage::Scope::READ_WRITE});
  gpkg.addExtension(geopackage::Extension{"line_index", "index", "Line Index", "R-TREE", geopackage::Scope::READ_WRITE});
  EXPECT_TRUE(gpkg.getExtension("Point Index").has_value());
  EXPECT_TRUE(gpkg.getExtension("Line Index").has_value());

  CLI::App app{"GeoPackageCPP CLI"};  

  Commands commands;
  DeleteExtensionCommand cmd{&app};
  commands.add(&cmd);

  int argc = 6;
  char const *argv[6] = {"geopackage-cli", "extension-delete", "-f", "data.gpkg", "-n", "Point Index"};

  app.parse(argc, argv);

  std::istringstream instream;
  std::ostringstream outstream;

  cmd.execute(instream, outstream);

  EXPECT_FALSE(gpkg.getExtension("Point Index").has_value());
  EXPECT_TRUE(gpkg.getExtension("Line Index").has_value());
  EXPECT_TRUE(std::filesystem::remove(fileName));
}