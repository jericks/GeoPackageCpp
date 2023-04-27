#include "tileMatrix/CreateTileMatrixCommand.hpp"

CreateTileMatrixCommand::CreateTileMatrixCommand(CLI::App* app): Command ("tilematrix-create") {
    CLI::App* cmd = app->add_subcommand("tilematrix-create", "Create a Tile Matrix");
    cmd->add_option("-f", options.fileName, "File")->required();
    cmd->add_option("-n", options.tableName, "Table Name")->required();
    cmd->add_option("-z", options.zoomLevel, "Zoom Level")->required();
    cmd->add_option("-m", options.matrixSize, "Matrix Size")->required();
    cmd->add_option("-t", options.tileSize, "Tile Size")->required();
    cmd->add_option("-p", options.pixelSize, "Pixel Size")->required();
}

void CreateTileMatrixCommand::execute(std::istream& istream, std::ostream& ostream) {
    geopackage::GeoPackage gpkg {options.fileName};
    gpkg.addTileMatrix(geopackage::TileMatrix{
        options.tableName,
        options.zoomLevel,
        geopackage::size::fromIntString(options.matrixSize),
        geopackage::size::fromIntString(options.tileSize),
        geopackage::size::fromDoubleString(options.pixelSize)
    });
}