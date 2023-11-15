#include "layerStyle/LoadLayerStyleCommand.hpp"

LoadLayerStyleCommand::LoadLayerStyleCommand(CLI::App* app): Command ("layerstyle-load") {
    CLI::App* cmd = app->add_subcommand("layerstyle-load", "Load layer style by id");
    cmd->add_option("-f", options.fileName, "File")->required();
    cmd->add_option("-i", options.id, "ID")->required();
    cmd->add_option("-s", options.styleFileName, "Style File")->required();
}

void LoadLayerStyleCommand::execute(std::istream& istream, std::ostream& ostream) {
    geopackage::GeoPackage gpkg {options.fileName};
    auto layerStyle = gpkg.getLayerStyle(options.id);
    if (layerStyle.has_value()) {
        bool isSld = hasEnding(options.styleFileName, ".sld");
        std::ifstream inputStream(options.styleFileName);
        std::stringstream buffer;
        buffer << inputStream.rdbuf();
        gpkg.updateLayerStyle(geopackage::LayerStyle {
            layerStyle->getId(),
            layerStyle->getTableCatalog(),
            layerStyle->getTableSchema(),
            layerStyle->getTableName(),
            layerStyle->getGeometryColumn(),
            layerStyle->getStyleName(),
            isSld ? layerStyle->getStyleQML() : buffer.str(),
            isSld ? buffer.str() : layerStyle->getStyleSLD(),
            layerStyle->getUseAsDefault(),
            layerStyle->getDescription(),
            layerStyle->getOwner(),
            layerStyle->getUi(),
            layerStyle->getUpdateTime()
        });
    }
}

bool LoadLayerStyleCommand::hasEnding (std::string const &fullString, std::string const &ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}