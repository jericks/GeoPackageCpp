#include "layerStyle/CreateLayerStyleCommand.hpp"

CreateLayerStyleCommand::CreateLayerStyleCommand(CLI::App* app): Command ("layerstyle-create") {
    CLI::App* cmd = app->add_subcommand("layerstyle-create", "Create a layer style");
    cmd->add_option("-f", options.fileName, "File")->required();
    cmd->add_option("-c", options.tableCatalog, "Catalog");
    cmd->add_option("-a", options.tableSchema, "Schema");
    cmd->add_option("-n", options.tableName, "Name")->required();
    cmd->add_option("-g", options.geometryColumn, "Geometry Column")->required();
    cmd->add_option("-t", options.styleName, "Style Name")->required();
    cmd->add_option("-q", options.styleQML, "Style QML");
    cmd->add_option("-s", options.styleSLD, "Style SLD");
    cmd->add_option("-l", options.useAsDefault, "Is Default");
    cmd->add_option("-d", options.description, "Description");
    cmd->add_option("-o", options.owner, "Owner");
    cmd->add_option("-u", options.ui, "UI");
}

void CreateLayerStyleCommand::execute(std::istream& istream, std::ostream& ostream) {
    geopackage::GeoPackage gpkg {options.fileName};
    gpkg.addLayerStyle(geopackage::LayerStyle{
        options.tableCatalog,
        options.tableSchema,
        options.tableName,
        options.geometryColumn,
        options.styleName,
        options.styleQML,
        options.styleSLD,
        options.useAsDefault,
        options.description,
        options.owner,
        options.ui
    });
}