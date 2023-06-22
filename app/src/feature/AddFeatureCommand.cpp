#include "feature/AddFeatureCommand.hpp"

AddFeatureCommand::AddFeatureCommand(CLI::App* app): Command ("feature-add") {
    CLI::App* cmd = app->add_subcommand("feature-add", "Add a Feature to a Layer");
    cmd->add_option("-f", options.fileName, "File name")->required();
    cmd->add_option("-n", options.layerName, "Layer name")->required();
    cmd->add_option("-g", options.geometry, "Geometry")->required();
    cmd->add_option("-v", options.values, "Value")->required();
}

void AddFeatureCommand::execute(std::istream& istream, std::ostream& ostream) {
    geopackage::GeoPackage gpkg {options.fileName};
    geopackage::WKTReader wktReader;
    std::unique_ptr<geopackage::Geometry> geometry = wktReader.read(options.geometry);
    std::map<std::string, std::any> values;
    for(std::pair<std::string, std::string> value : options.values) {
        values[value.first] = value.second;
    }
    geopackage::Feature feature {std::move(geometry), values};
    gpkg.addFeature(options.layerName, feature);
}