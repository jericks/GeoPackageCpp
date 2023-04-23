#include "tileMatrixSet/GetTileMatrixSetCommand.hpp"

GetTileMatrixSetCommand::GetTileMatrixSetCommand(CLI::App* app): Command ("tilematrixset-get") {
    CLI::App* cmd = app->add_subcommand("tilematrixset-get", "Get Tile Matrix Set by table name");
    cmd->add_option("-f", options.fileName, "File")->required();
    cmd->add_option("-n", options.tableName, "Table Name")->required();
}

void GetTileMatrixSetCommand::execute(std::istream& istream, std::ostream& ostream) {
    geopackage::GeoPackage gpkg {options.fileName};
    auto tileMatrixSet = gpkg.getTileMatrixSet(options.tableName);
    if (tileMatrixSet.has_value()) {
        auto t = tileMatrixSet.value();
        ostream << "Name: " << t.getTableName() << "\n";
        ostream << "SRS ID: " << t.getSrsId() << "\n";
        ostream << "Bounds: " << t.getBounds() << "\n";
    }
}