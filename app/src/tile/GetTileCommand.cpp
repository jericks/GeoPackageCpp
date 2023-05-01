#include "tile/GetTileCommand.hpp"

GetTileCommand::GetTileCommand(CLI::App* app): Command ("tile-get") {
    CLI::App* cmd = app->add_subcommand("tile-get", "Get a tile and save it");
    cmd->add_option("-f", options.fileName, "File name")->required();
    cmd->add_option("-n", options.tableName, "Table name")->required();
    cmd->add_option("-z", options.zoom, "Zoom")->required();
    cmd->add_option("-c", options.column, "Column")->required();
    cmd->add_option("-r", options.row, "Row")->required();
    cmd->add_option("-o", options.outputFileName, "Output file name")->required();
}

void GetTileCommand::execute(std::istream& istream, std::ostream& ostream) {
    geopackage::GeoPackage gpkg {options.fileName};
    auto tile = gpkg.getTile(options.tableName, options.zoom, options.column, options.row);
    if (tile) {
        tile->save(options.outputFileName);
    }
}