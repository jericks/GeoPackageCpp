#include "tileMatrix/ListTileMatrixCommand.hpp"

ListTileMatrixCommand::ListTileMatrixCommand(CLI::App* app): Command ("tilematrix-list") {
    CLI::App* cmd = app->add_subcommand("tilematrix-list", "List tile matrix");
    cmd->add_option("-f", options.fileName, "File")->required();
    cmd->add_option("-n", options.tableName, "Table Name");
}

void ListTileMatrixCommand::execute(std::istream& istream, std::ostream& ostream) {
    geopackage::GeoPackage gpkg {options.fileName};
    if (!options.tableName.empty()) {
        gpkg.tileMatrices(options.tableName, [&](geopackage::TileMatrix& tileMatrix) {
            ostream << "Table Name: " << tileMatrix.getTableName() << "\n";
            ostream << "Zoom Level: " << tileMatrix.getZoomLevel() << "\n";
            ostream << "Matrix Size: " << tileMatrix.getMatrixSize() << "\n";
            ostream << "Tile Size: " << tileMatrix.getTileSize() << "\n";
            ostream << "Pixel Size: " << tileMatrix.getPixelSize() << "\n";
            ostream << "\n";
        });
    } else {
        gpkg.tileMatrices([&](geopackage::TileMatrix& tileMatrix) {
            ostream << "Table Name: " << tileMatrix.getTableName() << "\n";
            ostream << "Zoom Level: " << tileMatrix.getZoomLevel() << "\n";
            ostream << "Matrix Size: " << tileMatrix.getMatrixSize() << "\n";
            ostream << "Tile Size: " << tileMatrix.getTileSize() << "\n";
            ostream << "Pixel Size: " << tileMatrix.getPixelSize() << "\n";
            ostream << "\n";
        });
    }
    
}