#include "feature/CountFeaturesCommand.hpp"

CountFeaturesCommand::CountFeaturesCommand(CLI::App* app): Command ("feature-count") {
    CLI::App* cmd = app->add_subcommand("feature-count", "Count the number of features");
    cmd->add_option("-f", options.fileName, "File name")->required();
    cmd->add_option("-n", options.layerName, "Layer name")->required();
}

void CountFeaturesCommand::execute(std::istream& istream, std::ostream& ostream) {
    geopackage::GeoPackage gpkg {options.fileName};
    int numberOfFeatures = gpkg.countFeatures(options.layerName);
    ostream << numberOfFeatures << "\n";
}