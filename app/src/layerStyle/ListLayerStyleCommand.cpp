#include "layerStyle/ListLayerStyleCommand.hpp"

ListLayerStyleCommand::ListLayerStyleCommand(CLI::App* app): Command ("layerstyle-list") {
    CLI::App* cmd = app->add_subcommand("layerstyle-list", "List layer styles");
    cmd->add_option("-f", options.fileName, "File")->required();
    cmd->add_option("-n", options.tableName, "Layer Name");
}

void ListLayerStyleCommand::execute(std::istream& istream, std::ostream& ostream) {
    geopackage::GeoPackage gpkg {options.fileName};
    auto fn = [&](geopackage::LayerStyle& s) {
        ostream << "ID: " << s.getId() << "\n";
        ostream << "Name: " << s.getTableName() << "\n";
        ostream << "Style Name: " << s.getStyleName() << "\n";
        ostream << "Description: " << s.getDescription() << "\n";
        ostream << "\n";
    };
    if (options.tableName.empty()) {
        gpkg.layerStyles(fn);        
    } else {
        gpkg.layerStylesForLayer(options.tableName, fn);
    }
    
}