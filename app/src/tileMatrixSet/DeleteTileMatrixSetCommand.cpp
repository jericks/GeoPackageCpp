#include "tileMatrixSet/DeleteTileMatrixSetCommand.hpp"

DeleteTileMatrixSetCommand::DeleteTileMatrixSetCommand(CLI::App* app): Command ("tilematrixset-delete") {
    CLI::App* cmd = app->add_subcommand("tilematrixset-delete", "Delete Tile Matrix Set by table name");
    cmd->add_option("-f", options.fileName, "File")->required();
    cmd->add_option("-n", options.tableName, "Table Name")->required();
}

void DeleteTileMatrixSetCommand::execute(std::istream& istream, std::ostream& ostream) {
    geopackage::GeoPackage gpkg {options.fileName};
    auto tileMatrixSet = gpkg.getTileMatrixSet(options.tableName);
    if (tileMatrixSet.has_value()) {
        gpkg.deleteTileMatrixSet(tileMatrixSet.value());
    }
}