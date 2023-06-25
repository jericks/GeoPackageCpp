#include "feature/DeleteFeatureCommand.hpp"

DeleteFeatureCommand::DeleteFeatureCommand(CLI::App* app): Command ("feature-delete") {
    CLI::App* cmd = app->add_subcommand("feature-delete", "Delete a Feature from a Layer");
    cmd->add_option("-f", options.fileName, "File name")->required();
    cmd->add_option("-n", options.layerName, "Layer name")->required();
    cmd->add_option("-i", options.id, "Feature ID")->required();
}

void DeleteFeatureCommand::execute(std::istream& istream, std::ostream& ostream) {
    geopackage::GeoPackage gpkg {options.fileName};
    auto feature = gpkg.getFeature(options.layerName, options.id);
    if (feature.has_value()) {
        auto f = feature.value();
        gpkg.deleteFeature(options.layerName, f);
    }
}