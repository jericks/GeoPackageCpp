#include "tileMatrixSet/CreateTileMatrixSetCommand.hpp"

CreateTileMatrixSetCommand::CreateTileMatrixSetCommand(CLI::App* app): Command ("tilematrixset-create") {
    CLI::App* cmd = app->add_subcommand("tilematrixset-create", "Create a Tile Matrix Set");
    cmd->add_option("-f", options.fileName, "File")->required();
    cmd->add_option("-n", options.tableName, "Table Name")->required();
    cmd->add_option("-b", options.bounds, "Bounds")->required();
    cmd->add_option("-s", options.srsId, "SRS ID")->required();
}

void CreateTileMatrixSetCommand::execute(std::istream& istream, std::ostream& ostream) {
    geopackage::GeoPackage gpkg {options.fileName};
    gpkg.addTileMatrixSet(geopackage::TileMatrixSet{
        options.tableName,
        options.srsId,
        geopackage::Bounds::fromString(options.bounds)
    });
}