#include "tile/ExportTilesCommand.hpp"

ExportTilesCommand::ExportTilesCommand(CLI::App* app): Command ("tile-export") {
    CLI::App* cmd = app->add_subcommand("tile-export", "Export tiles to a Directory");
    cmd->add_option("-f", options.fileName, "File name")->required();
    cmd->add_option("-n", options.tableName, "Table name")->required();
    cmd->add_option("-d", options.directory, "Directory")->required();
    cmd->add_option("-m", options.format, "Image Format")->required();
}

void ExportTilesCommand::execute(std::istream& istream, std::ostream& ostream) {
    geopackage::GeoPackage gpkg {options.fileName};
    gpkg.exportTilesToDirectory(options.tableName, options.format, options.directory);
}