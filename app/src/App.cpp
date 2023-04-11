#include <iostream>
#include "CLI/CLI.hpp"
#include "Commands.hpp"
#include "Command.hpp"
#include "ListCommand.hpp"
#include "CreateCommand.hpp"
#include "RandomFeaturesCommand.hpp"

#include "spatialref/CreateSpatialRefCommand.hpp"
#include "spatialref/DeleteSpatialRefCommand.hpp"
#include "spatialref/GetSpatialRefCommand.hpp"
#include "spatialref/ListSpatialRefCommand.hpp"

#include "content/CreateContentCommand.hpp"
#include "content/ListContentCommand.hpp"
#include "content/GetContentCommand.hpp"
#include "content/DeleteContentCommand.hpp"

#include "geometryColumn/ListGeometryColumnCommand.hpp"
#include "geometryColumn/GetGeometryColumnCommand.hpp"
#include "geometryColumn/DeleteGeometryColumnCommand.hpp"
#include "geometryColumn/CreateGeometryColumnCommand.hpp"

#include "extension/ListExtensionCommand.hpp"

int main(int argc, char *argv[]) {

    CLI::App app{"GeoPackage CLI"};
    app.require_subcommand(1);

    Commands commands;
    
    ListCommand listCommand(&app, &commands);
    commands.add(&listCommand);

    CreateCommand createCommand(&app);
    commands.add(&createCommand);

    RandomFeaturesCommand randomFeaturesCommand(&app);
    commands.add(&randomFeaturesCommand);

    // SpatialRef

    CreateSpatialRefCommand createSpatialRefCommand(&app);
    commands.add(&createSpatialRefCommand);

    DeleteSpatialRefCommand deleteSpatialRefCommand(&app);
    commands.add(&deleteSpatialRefCommand);

    GetSpatialRefCommand getSpatialRefCommand(&app);
    commands.add(&getSpatialRefCommand);

    ListSpatialRefCommand listSpatialRefCommand(&app);
    commands.add(&listSpatialRefCommand);

    // Content

    CreateContentCommand createContentCommand(&app);
    commands.add(&createContentCommand);

    ListContentCommand listContentCommand(&app);
    commands.add(&listContentCommand);

    GetContentCommand getContentCommand(&app);
    commands.add(&getContentCommand);

    DeleteContentCommand deleteContentCommand(&app);
    commands.add(&deleteContentCommand);

    // Geometry Column

    ListGeometryColumnCommand listGeometryColumnCommand(&app);
    commands.add(&listGeometryColumnCommand);

    GetGeometryColumnCommand getGeometryColumnCommand(&app);
    commands.add(&getGeometryColumnCommand);

    CreateGeometryColumnCommand createGeometryColumnCommand(&app);
    commands.add(&createGeometryColumnCommand);

    DeleteGeometryColumnCommand deleteGeometryColumnCommand(&app);
    commands.add(&deleteGeometryColumnCommand);

    CLI11_PARSE(app, argc, argv);

    for(Command* cmd : commands.get()) {
      if (app.got_subcommand(cmd->getName())) {
        cmd->execute(std::cin, std::cout);
        break;
      }
    }

    return 0;

}