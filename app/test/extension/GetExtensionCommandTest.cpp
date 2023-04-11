#include <sstream>
#include <iostream>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "extension/GetExtensionCommand.hpp"
#include "gtest/gtest.h"

TEST(GeoPackageCliTests, GetExtensionCommand) {
  
  const std::string fileName = "data.gpkg";
  geopackage::GeoPackage gpkg { fileName };
  EXPECT_TRUE(std::filesystem::exists(fileName));

  gpkg.addExtension(geopackage::Extension{"point_index", "index", "Point Index", "R-TREE", geopackage::Scope::READ_WRITE});
  gpkg.addExtension(geopackage::Extension{"line_index", "index", "Line Index", "R-TREE", geopackage::Scope::READ_WRITE});
  
  CLI::App app{"GeoPackageCPP CLI"};  

  Commands commands;
  GetExtensionCommand cmd{&app};
  commands.add(&cmd);

  int argc = 6;
  char const *argv[6] = {"geopackage-cli", "extension-get", "-f", "data.gpkg", "-n", "point_index"};

  app.parse(argc, argv);

  std::istringstream instream;
  std::ostringstream outstream;

  cmd.execute(instream, outstream);

  std::string result = outstream.str();
  ASSERT_EQ(std::string::npos, result.find("point_index"));
  ASSERT_EQ(std::string::npos, result.find("Point Index"));

  EXPECT_TRUE(std::filesystem::remove(fileName));
}