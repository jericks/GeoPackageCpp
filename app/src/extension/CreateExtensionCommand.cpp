#include "extension/CreateExtensionCommand.hpp"

CreateExtensionCommand::CreateExtensionCommand(CLI::App* app): Command ("extension-create") {
    CLI::App* cmd = app->add_subcommand("extension-create", "Create a extension");
    cmd->add_option("-f", options.fileName, "File")->required();
    cmd->add_option("-n", options.tableName, "Table Name")->required();
    cmd->add_option("-c", options.columnName, "Column Name")->required();
    cmd->add_option("-e", options.extensionName, "Extension Name")->required();
    cmd->add_option("-d", options.definition, "Definition")->required();
    cmd->add_option("-s", options.scope, "Scope")->required();
}

void CreateExtensionCommand::execute(std::istream& istream, std::ostream& ostream) {
    geopackage::GeoPackage gpkg {options.fileName};
    gpkg.addExtension(geopackage::Extension{
        options.tableName,
        options.columnName,
        options.extensionName,
        options.definition,
        geopackage::scope::getScope(options.scope)
    });
}