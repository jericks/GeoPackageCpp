#include "content/CreateContentCommand.hpp"

CreateContentCommand::CreateContentCommand(CLI::App* app): Command ("content-create") {
    CLI::App* cmd = app->add_subcommand("content-create", "Create a content");
    cmd->add_option("-f", options.fileName, "File")->required();
    cmd->add_option("-n", options.tableName, "Name")->required();
    cmd->add_option("-t", options.dataType, "Data Type")->required();
    cmd->add_option("-i", options.identifier, "Identifier")->required();
    cmd->add_option("-d", options.description, "Description")->required();
    cmd->add_option("-b", options.bounds, "Bounds")->required();
    cmd->add_option("-s", options.srsId, "SRS ID")->required();
}

void CreateContentCommand::execute(std::istream& istream, std::ostream& ostream) {
    geopackage::GeoPackage gpkg {options.fileName};
    gpkg.addContent(geopackage::Content{
        options.tableName,
        geopackage::datatype::getDataType(options.dataType),
        options.identifier,
        options.description,
        "", // Last Change @TODO Fix me
        geopackage::Bounds::fromString(options.bounds),
        options.srsId
    });
}