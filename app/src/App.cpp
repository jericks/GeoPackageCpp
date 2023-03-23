#include <iostream>
#include "CLI/CLI.hpp"
#include "Commands.hpp"
#include "Command.hpp"
#include "ListCommand.hpp"
#include "CreateCommand.hpp"
#include "RandomFeaturesCommand.hpp"

#include "CreateSpatialRefCommand.hpp"
#include "GetSpatialRefCommand.hpp"
#include "ListSpatialRefCommand.hpp"


int main(int argc, char *argv[]) {

    CLI::App app{"GeoPackage CLI"};
    app.require_subcommand(1);

    Commands commands;
    
    ListCommand listCommand(&app, &commands);
    commands.add(&listCommand);

    CreateCommand createCommand(&app);
    commands.add(&createCommand);

    CreateSpatialRefCommand createSpatialRefCommand(&app);
    commands.add(&createSpatialRefCommand);

    GetSpatialRefCommand getSpatialRefCommand(&app);
    commands.add(&getSpatialRefCommand);

    ListSpatialRefCommand listSpatialRefCommand(&app);
    commands.add(&listSpatialRefCommand);

    RandomFeaturesCommand randomFeaturesCommand(&app);
    commands.add(&randomFeaturesCommand);

    CLI11_PARSE(app, argc, argv);

    for(Command* cmd : commands.get()) {
      if (app.got_subcommand(cmd->getName())) {
        cmd->execute(std::cin, std::cout);
        break;
      }
    }

    return 0;

}