#include "tile/CreateGeodeticTileLayerCommand.hpp"

CreateGeodeticTileLayerCommand::CreateGeodeticTileLayerCommand(CLI::App* app): Command ("tile-geodetic-create") {
    CLI::App* cmd = app->add_subcommand("tile-geodetic-create", "Creatc a Geodetic Tile Table");
    cmd->add_option("-f", options.fileName, "File")->required();
    cmd->add_option("-n", options.tableName, "Table Name")->required();
    cmd->add_option("-s", options.tileSize, "Tile Size")->required();
    cmd->add_option("-z", options.maxZoomLevel, "Max Zoom Level")->required();
}

void CreateGeodeticTileLayerCommand::execute(std::istream& istream, std::ostream& ostream) {
    geopackage::GeoPackage gpkg {options.fileName};
    gpkg.createGlobalGeodeticTileLayer(options.tableName, options.tileSize, options.maxZoomLevel);
}