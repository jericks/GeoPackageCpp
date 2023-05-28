#include "feature/CreateFeatureLayerCommand.hpp"

CreateFeatureLayerCommand::CreateFeatureLayerCommand(CLI::App* app): Command ("feature-create") {
    CLI::App* cmd = app->add_subcommand("feature-create", "Create a feature layer");
    cmd->add_option("-f", options.fileName, "File name")->required();
    cmd->add_option("-n", options.layerName, "Layer name")->required();
    cmd->add_option("-i", options.idName, "ID name")->required();
    cmd->add_option("-c", options.geometryName, "Geometry Name")->required();
    cmd->add_option("-g", options.geometryType, "Geometry Type")->required();
    cmd->add_option("-d", options.dimension, "Geometry Dimension")->required();
    cmd->add_option("-s", options.srsId, "SRS ID")->required();
    cmd->add_option("-e", options.fields, "Field")->required();
}

void CreateFeatureLayerCommand::execute(std::istream& istream, std::ostream& ostream) {
    geopackage::GeoPackage gpkg {options.fileName};

    std::vector<geopackage::Field> fields;
    for(auto fld : options.fields) {
        fields.push_back(geopackage::Field(fld.first, geopackage::fieldtype::getFieldType(fld.second)));
    }

    geopackage::Schema schema {
        options.layerName,
        options.idName,
        geopackage::GeometryField{
            options.geometryName, 
            geopackage::geometrytype::getGeometryType(options.geometryType), 
            geopackage::dimension::fromString(options.dimension),
            options.srsId
        },
        fields
    };
    
    geopackage::Bounds bounds = geopackage::Bounds::getGeodeticBounds();
    gpkg.createFeatureLayer(schema, bounds);
}