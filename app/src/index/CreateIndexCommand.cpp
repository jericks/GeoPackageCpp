#include "index/CreateIndexCommand.hpp"

CreateIndexCommand::CreateIndexCommand(CLI::App* app): Command ("index-create") {
    CLI::App* cmd = app->add_subcommand("index-create", "Create a spatial index");
    cmd->add_option("-f", options.fileName, "File")->required();
    cmd->add_option("-n", options.tableName, "Name")->required();
}

void CreateIndexCommand::execute(std::istream& istream, std::ostream& ostream) {
    geopackage::GeoPackage gpkg {options.fileName};
    gpkg.addIndexExtension(options.tableName);
    gpkg.indexLayer(options.tableName);
}