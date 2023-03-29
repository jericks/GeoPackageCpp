#include "content/ListContentCommand.hpp"

ListContentCommand::ListContentCommand(CLI::App* app): Command ("content-list") {
    CLI::App* cmd = app->add_subcommand("content-list", "List content entries");
    cmd->add_option("-f", options.fileName, "File")->required();
}

void ListContentCommand::execute(std::istream& istream, std::ostream& ostream) {
    geopackage::GeoPackage gpkg {options.fileName};
    gpkg.contents([&](geopackage::Content& c) {
        ostream << "Name: " << c.getTableName() << "\n";
        ostream << "Data Type: " << c.getDataType() << "\n";
        ostream << "Identifier: " << c.getIdentifier() << "\n";
        ostream << "Description: " << c.getDescription() << "\n";
        ostream << "Bounds: " << c.getBounds() << "\n";
        ostream << "SRS ID: " << c.getSrsId() << "\n";
        ostream << "\n";
    });
}