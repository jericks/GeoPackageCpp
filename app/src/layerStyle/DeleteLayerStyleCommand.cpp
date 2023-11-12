#include "layerStyle/DeleteLayerStyleCommand.hpp"

DeleteLayerStyleCommand::DeleteLayerStyleCommand(CLI::App* app): Command ("layerstyle-delete") {
    CLI::App* cmd = app->add_subcommand("layerstyle-delete", "Delete Layer Style by ID");
    cmd->add_option("-f", options.fileName, "File")->required();
    cmd->add_option("-i", options.id, "ID")->required();
}

void DeleteLayerStyleCommand::execute(std::istream& istream, std::ostream& ostream) {
    geopackage::GeoPackage gpkg {options.fileName};
    auto layerStyle = gpkg.getLayerStyle(options.id);
    if (layerStyle.has_value()) {
        auto s = layerStyle.value();
        gpkg.deleteLayerStyle(s);
    }
}