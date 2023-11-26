#include "index/DeleteIndexCommand.hpp"

DeleteIndexCommand::DeleteIndexCommand(CLI::App* app): Command ("index-delete") {
    CLI::App* cmd = app->add_subcommand("index-delete", "Delete a spatial index");
    cmd->add_option("-f", options.fileName, "File")->required();
    cmd->add_option("-n", options.tableName, "Name")->required();
}

void DeleteIndexCommand::execute(std::istream& istream, std::ostream& ostream) {
    geopackage::GeoPackage gpkg {options.fileName};
    gpkg.deleteIndex(options.tableName);
}