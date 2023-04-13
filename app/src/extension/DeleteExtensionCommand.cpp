#include "extension/DeleteExtensionCommand.hpp"

DeleteExtensionCommand::DeleteExtensionCommand(CLI::App* app): Command ("extension-delete") {
    CLI::App* cmd = app->add_subcommand("extension-delete", "Delete extension by name");
    cmd->add_option("-f", options.fileName, "File")->required();
    cmd->add_option("-n", options.name, "Name")->required();
}

void DeleteExtensionCommand::execute(std::istream& istream, std::ostream& ostream) {
    geopackage::GeoPackage gpkg {options.fileName};
    auto extension = gpkg.getExtension(options.name);
    if (extension.has_value()) {
        auto e = extension.value();
        gpkg.deleteExtension(e);
    }
}