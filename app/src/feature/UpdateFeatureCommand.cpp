#include "feature/UpdateFeatureCommand.hpp"

UpdateFeatureCommand::UpdateFeatureCommand(CLI::App* app): Command ("feature-update") {
    CLI::App* cmd = app->add_subcommand("feature-update", "Update a Feature in a Layer");
    cmd->add_option("-f", options.fileName, "File name")->required();
    cmd->add_option("-n", options.layerName, "Layer name")->required();
    cmd->add_option("-i", options.id, "Feature ID")->required();
    cmd->add_option("-g", options.geometry, "Geometry");
    cmd->add_option("-v", options.values, "Value");
}

void UpdateFeatureCommand::execute(std::istream& istream, std::ostream& ostream) {
    geopackage::GeoPackage gpkg {options.fileName};
    auto feature = gpkg.getFeature(options.layerName, options.id);
    if (feature.has_value()) {
        auto f = feature.value();
        if (!options.geometry.empty()) {    
            geopackage::WKTReader wktReader;
            f.setGeometry(wktReader.read(options.geometry));
        }
        for(std::pair<std::string, std::string> value : options.values) {
            f.setAttribute(value.first, value.second);
        }
        gpkg.updateFeature(options.layerName, f);
    }  
}