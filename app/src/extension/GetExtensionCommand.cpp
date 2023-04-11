#include "extension/GetExtensionCommand.hpp"

GetExtensionCommand::GetExtensionCommand(CLI::App* app): Command ("extension-get") {
    CLI::App* cmd = app->add_subcommand("extension-get", "Get extension by name");
    cmd->add_option("-f", options.fileName, "File")->required();
    cmd->add_option("-n", options.name, "Name")->required();
}

void GetExtensionCommand::execute(std::istream& istream, std::ostream& ostream) {
    geopackage::GeoPackage gpkg {options.fileName};
    auto extension = gpkg.getExtension(options.name);
    if (extension.has_value()) {
        ostream << "Name: " << extension->getTableName() << "\n";
        ostream << "Column Name: " << extension->getColumnName() << "\n";
        ostream << "Extension Name: " << extension->getExtensionName() << "\n";
        ostream << "Definition: " << extension->getDefinition() << "\n";
        ostream << "Scope: " << geopackage::scope::toString(extension->getScope()) << "\n";
        ostream << "\n";
    }
}