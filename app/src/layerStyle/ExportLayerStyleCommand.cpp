#include "layerStyle/ExportLayerStyleCommand.hpp"

ExportLayerStyleCommand::ExportLayerStyleCommand(CLI::App* app): Command ("layerstyle-export") {
    CLI::App* cmd = app->add_subcommand("layerstyle-export", "Export layer style by id");
    cmd->add_option("-f", options.fileName, "File")->required();
    cmd->add_option("-i", options.id, "ID")->required();
    cmd->add_option("-s", options.styleFileName, "Style File")->required();
}

void ExportLayerStyleCommand::execute(std::istream& istream, std::ostream& ostream) {
    geopackage::GeoPackage gpkg {options.fileName};
    auto layerStyle = gpkg.getLayerStyle(options.id);
    if (layerStyle.has_value()) {
        bool isSld = hasEnding(options.styleFileName, ".sld");
        std::string style = isSld ? layerStyle->getStyleSLD() : layerStyle->getStyleQML();
        std::ofstream outFile;
        outFile.open (options.styleFileName);
        outFile << style;
        outFile.close();
    }
}

bool ExportLayerStyleCommand::hasEnding (std::string const &fullString, std::string const &ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}