#include "layerStyle/GetLayerStyleCommand.hpp"

GetLayerStyleCommand::GetLayerStyleCommand(CLI::App* app): Command ("layerstyle-get") {
    CLI::App* cmd = app->add_subcommand("layerstyle-get", "Get layer style by id");
    cmd->add_option("-f", options.fileName, "File")->required();
    cmd->add_option("-i", options.id, "ID")->required();
}

void GetLayerStyleCommand::execute(std::istream& istream, std::ostream& ostream) {
    geopackage::GeoPackage gpkg {options.fileName};
    auto layerStyle = gpkg.getLayerStyle(options.id);
    if (layerStyle.has_value()) {
        auto s = layerStyle.value();
        ostream << "ID: " << s.getId() << "\n";
        ostream << "Name: " << s.getTableName() << "\n";
        ostream << "Style Name: " << s.getStyleName() << "\n";
        ostream << "Description: " << s.getDescription() << "\n";
        if (!s.getStyleSLD().empty()) {
            ostream << "SLD:\n" << s.getStyleSLD() << "\n";
        }
        if (!s.getStyleQML().empty()) {
            ostream << "QML:\n" << s.getStyleQML() << "\n";
        }
        ostream << "\n";
    }
    
    
}