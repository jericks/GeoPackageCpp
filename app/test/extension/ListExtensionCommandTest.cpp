#include <sstream>
#include <iostream>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "extension/ListExtensionCommand.hpp"
#include "gtest/gtest.h"

TEST(GeoPackageCliTests, ListExtensionCommand) {
  
  const std::string fileName = "data.gpkg";
  geopackage::GeoPackage gpkg { fileName };
  EXPECT_TRUE(std::filesystem::exists(fileName));

  gpkg.addExtension(geopackage::Extension{"point_index", "index", "Point Index", "R-TREE", geopackage::Scope::READ_WRITE});
  gpkg.addExtension(geopackage::Extension{"line_index", "index", "Line Index", "R-TREE", geopackage::Scope::READ_WRITE});
  
  CLI::App app{"GeoPackageCPP CLI"};  

  Commands commands;
  ListExtensionCommand cmd{&app};
  commands.add(&cmd);

  int argc = 4;
  char const *argv[4] = {"geopackage-cli", "extension-list", "-f", "data.gpkg"};

  app.parse(argc, argv);

  std::istringstream instream;
  std::ostringstream outstream;

  cmd.execute(instream, outstream);

  std::string result = outstream.str();
  std::cout << result << "\n";
  ASSERT_NE(std::string::npos, result.find("point_index"));
  ASSERT_NE(std::string::npos, result.find("line_index"));

  EXPECT_TRUE(std::filesystem::remove(fileName));
}