#include <sstream>
#include <iostream>
#include "CLI/CLI.hpp"
#include "Command.hpp"
#include "Commands.hpp"
#include "CreateCommand.hpp"
#include "gtest/gtest.h"

TEST(GeoPackageCliTests, create_test) {
  
  CLI::App app{"GeoPackageCPP CLI"};  

  Commands commands;
  CreateCommand createCommand{&app};
  commands.add(&createCommand);

  int argc = 4;
  char const *argv[4] = {"geopackage-cli", "create", "-f", "data.gpkg"};

  app.parse(argc, argv);

  std::istringstream instream;
  std::ostringstream outstream;

  createCommand.execute(instream, outstream);

  std::string result = outstream.str();
  ASSERT_NE(std::string::npos, result.find("data.gpkg"));

}