#include "tileMatrix/GetTileMatrixCommand.hpp"

GetTileMatrixCommand::GetTileMatrixCommand(CLI::App* app): Command ("tilematrix-get") {
    CLI::App* cmd = app->add_subcommand("tilematrix-get", "Get tile matrix");
    cmd->add_option("-f", options.fileName, "File")->required();
    cmd->add_option("-n", options.tableName, "Table Name");
    cmd->add_option("-z", options.zoomLevel, "Zoom Level");
}

void GetTileMatrixCommand::execute(std::istream& istream, std::ostream& ostream) {
    geopackage::GeoPackage gpkg {options.fileName};
    auto tileMatrix = gpkg.getTileMatrix(options.tableName, options.zoomLevel);
    if (tileMatrix.has_value()) {
        ostream << "Table Name: " << tileMatrix->getTableName() << "\n";
        ostream << "Zoom Level: " << tileMatrix->getZoomLevel() << "\n";
        ostream << "Matrix Size: " << tileMatrix->getMatrixSize() << "\n";
        ostream << "Tile Size: " << tileMatrix->getTileSize() << "\n";
        ostream << "Pixel Size: " << tileMatrix->getPixelSize() << "\n";
    }
    
}