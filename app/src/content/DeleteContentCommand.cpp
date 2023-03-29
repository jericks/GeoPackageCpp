#include "content/DeleteContentCommand.hpp"

DeleteContentCommand::DeleteContentCommand(CLI::App* app): Command ("content-delete") {
    CLI::App* cmd = app->add_subcommand("content-delete", "Delete content by name");
    cmd->add_option("-f", options.fileName, "File")->required();
    cmd->add_option("-n", options.name, "Name")->required();
}

void DeleteContentCommand::execute(std::istream& istream, std::ostream& ostream) {
    geopackage::GeoPackage gpkg {options.fileName};
    auto content = gpkg.getContent(options.name);
    if (content.has_value()) {
        auto c = content.value();
        gpkg.deleteContent(c);
    }
}