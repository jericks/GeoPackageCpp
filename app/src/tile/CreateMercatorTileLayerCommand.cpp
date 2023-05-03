#include "tile/CreateMercatorTileLayerCommand.hpp"

CreateMercatorTileLayerCommand::CreateMercatorTileLayerCommand(CLI::App* app): Command ("tile-mercator-create") {
    CLI::App* cmd = app->add_subcommand("tile-mercator-create", "Creatc a Mercator Tile Table");
    cmd->add_option("-f", options.fileName, "File")->required();
    cmd->add_option("-n", options.tableName, "Table Name")->required();
    cmd->add_option("-s", options.tileSize, "Tile Size")->required();
    cmd->add_option("-z", options.maxZoomLevel, "Max Zoom Level")->required();
}

void CreateMercatorTileLayerCommand::execute(std::istream& istream, std::ostream& ostream) {
    geopackage::GeoPackage gpkg {options.fileName};
    gpkg.createGlobalMercatorTileLayer(options.tableName, options.tileSize, options.maxZoomLevel);
}