#include "feature/DeleteAllFeatureCommand.hpp"

DeleteAllFeatureCommand::DeleteAllFeatureCommand(CLI::App* app): Command ("feature-delete-all") {
    CLI::App* cmd = app->add_subcommand("feature-delete-all", "Delete All Features in a Layer");
    cmd->add_option("-f", options.fileName, "File name")->required();
    cmd->add_option("-n", options.layerName, "Layer name")->required();
}

void DeleteAllFeatureCommand::execute(std::istream& istream, std::ostream& ostream) {
    geopackage::GeoPackage gpkg {options.fileName};
    gpkg.deleteAllFeatures(options.layerName);
}