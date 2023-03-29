#include "content/GetContentCommand.hpp"

GetContentCommand::GetContentCommand(CLI::App* app): Command ("content-get") {
    CLI::App* cmd = app->add_subcommand("content-get", "Get content by name");
    cmd->add_option("-f", options.fileName, "File")->required();
    cmd->add_option("-n", options.name, "Name")->required();
}

void GetContentCommand::execute(std::istream& istream, std::ostream& ostream) {
    geopackage::GeoPackage gpkg {options.fileName};
    auto content = gpkg.getContent(options.name);
    if (content.has_value()) {
        ostream << "Name: " << content->getTableName() << "\n";
        ostream << "Data Type: " << content->getDataType() << "\n";
        ostream << "Identifier: " << content->getIdentifier() << "\n";
        ostream << "Description: " << content->getDescription() << "\n";
        ostream << "Bounds: " << content->getBounds() << "\n";
        ostream << "SRS ID: " << content->getSrsId() << "\n";
        ostream << "\n";
    }
}