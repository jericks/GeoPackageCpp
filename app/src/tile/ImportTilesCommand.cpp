#include "tile/ImportTilesCommand.hpp"

ImportTilesCommand::ImportTilesCommand(CLI::App* app): Command ("tile-import") {
    CLI::App* cmd = app->add_subcommand("tile-import", "Import tiles from a Directory");
    cmd->add_option("-f", options.fileName, "File name")->required();
    cmd->add_option("-n", options.tableName, "Table name")->required();
    cmd->add_option("-d", options.directory, "Directory")->required();
}

void ImportTilesCommand::execute(std::istream& istream, std::ostream& ostream) {
    geopackage::GeoPackage gpkg {options.fileName};
    gpkg.loadTilesFromDirectory(options.tableName, options.directory);
}