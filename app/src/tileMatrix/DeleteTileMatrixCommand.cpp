#include "tileMatrix/DeleteTileMatrixCommand.hpp"

DeleteTileMatrixCommand::DeleteTileMatrixCommand(CLI::App* app): Command ("tilematrix-delete") {
    CLI::App* cmd = app->add_subcommand("tilematrix-delete", "Delete Tile Matrix  by table name and zoom level");
    cmd->add_option("-f", options.fileName, "File")->required();
    cmd->add_option("-n", options.tableName, "Table Name")->required();
    cmd->add_option("-z", options.zoomLevel, "Zoom Level");
}

void DeleteTileMatrixCommand::execute(std::istream& istream, std::ostream& ostream) {
    geopackage::GeoPackage gpkg {options.fileName};
    if (options.zoomLevel > -1) {
        auto tileMatrix = gpkg.getTileMatrix(options.tableName, options.zoomLevel);
        if (tileMatrix.has_value()) {
            gpkg.deleteTileMatrix(tileMatrix.value());
        }
    } else {
        gpkg.tileMatrices(options.tableName, [&](geopackage::TileMatrix& tileMatrix) {
            gpkg.deleteTileMatrix(tileMatrix);
        });
    }
}