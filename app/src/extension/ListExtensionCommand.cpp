#include "extension/ListExtensionCommand.hpp"

ListExtensionCommand::ListExtensionCommand(CLI::App* app): Command ("extension-list") {
    CLI::App* cmd = app->add_subcommand("extension-list", "List extension entries");
    cmd->add_option("-f", options.fileName, "File")->required();
}

void ListExtensionCommand::execute(std::istream& istream, std::ostream& ostream) {
    geopackage::GeoPackage gpkg {options.fileName};
    gpkg.extensions([&](geopackage::Extension& c) {
        ostream << "Name: " << c.getTableName() << "\n";
        ostream << "Column Name: " << c.getColumnName() << "\n";
        ostream << "Extension Name: " << c.getExtensionName() << "\n";
        ostream << "Definition: " << c.getDefinition() << "\n";
        ostream << "Scope: " << geopackage::scope::toString(c.getScope()) << "\n";
        ostream << "\n";
    });
}