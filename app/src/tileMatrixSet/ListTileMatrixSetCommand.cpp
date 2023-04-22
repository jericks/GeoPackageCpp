#include "tileMatrixSet/ListTileMatrixSetCommand.hpp"

ListTileMatrixSetCommand::ListTileMatrixSetCommand(CLI::App* app): Command ("tilematrixset-list") {
    CLI::App* cmd = app->add_subcommand("tilematrixset-list", "List tile matrix sets");
    cmd->add_option("-f", options.fileName, "File")->required();
}

void ListTileMatrixSetCommand::execute(std::istream& istream, std::ostream& ostream) {
    geopackage::GeoPackage gpkg {options.fileName};
    gpkg.tileMatrixSets([&](geopackage::TileMatrixSet& tileMatrixSet) {
        ostream << "Name: " << tileMatrixSet.getTableName() << "\n";
        ostream << "SRS ID: " << tileMatrixSet.getSrsId() << "\n";
        ostream << "Bounds: " << tileMatrixSet.getBounds() << "\n";
        ostream << "\n";
    });
}