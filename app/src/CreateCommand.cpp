#include "CreateCommand.hpp"

CreateCommand::CreateCommand(CLI::App* app): Command ("create") {
    CLI::App* cmd = app->add_subcommand("create", "Create a blank GeoPackage");
    cmd->add_option("-f", options.fileName, "File")->required();
}

void CreateCommand::execute(std::istream& istream, std::ostream& ostream) {
    geopackage::GeoPackage gpkg {options.fileName};
    ostream << options.fileName << std::endl;
}