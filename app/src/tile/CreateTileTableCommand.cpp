#include "tile/CreateTileTableCommand.hpp"

CreateTileTableCommand::CreateTileTableCommand(CLI::App* app): Command ("tiletable-create") {
    CLI::App* cmd = app->add_subcommand("tiletable-create", "Create a Tile Table");
    cmd->add_option("-f", options.fileName, "File")->required();
    cmd->add_option("-n", options.tableName, "Table Name")->required();
}

void CreateTileTableCommand::execute(std::istream& istream, std::ostream& ostream) {
    geopackage::GeoPackage gpkg {options.fileName};
    gpkg.createTileTable(options.tableName);
}