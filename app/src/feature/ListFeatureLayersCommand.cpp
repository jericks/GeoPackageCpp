#include "feature/ListFeatureLayersCommand.hpp"

ListFeatureLayersCommand::ListFeatureLayersCommand(CLI::App* app): Command ("feature-list") {
    CLI::App* cmd = app->add_subcommand("feature-list", "List feature layers");
    cmd->add_option("-f", options.fileName, "File name")->required();
}

void ListFeatureLayersCommand::execute(std::istream& istream, std::ostream& ostream) {
    geopackage::GeoPackage gpkg {options.fileName};
    gpkg.contents(geopackage::DataType::FEATURES, [&](geopackage::Content& c) {
        ostream << c.getTableName() << "\n";
    });
}