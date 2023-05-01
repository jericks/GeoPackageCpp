#include "tile/DeleteTileCommand.hpp"

DeleteTileCommand::DeleteTileCommand(CLI::App* app): Command ("tile-delete") {
    CLI::App* cmd = app->add_subcommand("tile-delete", "Delete a Tile");
    cmd->add_option("-f", options.fileName, "File name")->required();
    cmd->add_option("-n", options.tableName, "Table name")->required();
    cmd->add_option("-z", options.zoom, "Zoom")->required();
    cmd->add_option("-c", options.column, "Column")->required();
    cmd->add_option("-r", options.row, "Row")->required();
}

void DeleteTileCommand::execute(std::istream& istream, std::ostream& ostream) {
    geopackage::GeoPackage gpkg {options.fileName};
    gpkg.deleteTile(options.tableName, geopackage::Tile{options.zoom, options.column, options.row});
}