#include "feature/InfoFeatureCommand.hpp"

InfoFeatureCommand::InfoFeatureCommand(CLI::App* app): Command ("feature-info") {
    CLI::App* cmd = app->add_subcommand("feature-info", "Get information on features");
    cmd->add_option("-f", options.fileName, "File")->required();
    cmd->add_option("-n", options.tableName, " Name")->required();
}

void InfoFeatureCommand::execute(std::istream& istream, std::ostream& ostream) {
    geopackage::GeoPackage gpkg {options.fileName};
    auto content = gpkg.getContent(options.tableName);
    if (content) {
        ostream << "Information" << "\n";
        ostream << "-----------" << "\n";
        ostream << "Name: " << content->getTableName() << "\n";
        ostream << "Description: " << content->getDescription() << "\n";
        ostream << "SRS ID: " << content->getSrsId() << "\n";
        ostream << "Bounds: " << content->getBounds() << "\n";
        ostream << "# Features: " << gpkg.countFeatures(options.tableName) << "\n";
        ostream << "\n";
    }
    auto geometryColumn = gpkg.getGeometryColumn(options.tableName);
    if (geometryColumn.has_value()) {
        ostream << "Geometry Column" << "\n";
        ostream << "---------------" << "\n";
        ostream << "Name: " << geometryColumn->getColumnName() << "\n";
        ostream << "Type: " << geopackage::geometrytype::toString(geometryColumn->getGeometryType()) << "\n";
        ostream << "Dimension: " << geopackage::dimension::toString(geometryColumn->getDimension()) << "\n";
        ostream << "\n";
    }
    geopackage::Schema schema = gpkg.getSchema(options.tableName);
    ostream << "Fields" << "\n";
    ostream << "------" << "\n";
    ostream << "Key Field: " << schema.getKey() << "\n";
    for (auto &fld : schema.getFields()) {
        ostream << fld.getName() << " " << fld.getType() << "\n";
    }
}