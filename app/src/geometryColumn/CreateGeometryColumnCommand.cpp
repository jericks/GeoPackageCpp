#include "geometryColumn/CreateGeometryColumnCommand.hpp"

CreateGeometryColumnCommand::CreateGeometryColumnCommand(CLI::App* app): Command ("geometrycolumn-create") {
    CLI::App* cmd = app->add_subcommand("geometrycolumn-create", "Create a Geometry Column");
    cmd->add_option("-f", options.fileName, "File")->required();
    cmd->add_option("-n", options.tableName, "Name")->required();
    cmd->add_option("-c", options.columnName, "Column Name")->required();
    cmd->add_option("-g", options.geometryType, "Geometry Type")->required();
    cmd->add_option("-s", options.srsId, "SRS ID")->required();
    cmd->add_option("-z", options.z, "Z")->required();
    cmd->add_option("-m", options.m, "M")->required();
}

void CreateGeometryColumnCommand::execute(std::istream& istream, std::ostream& ostream) {
    geopackage::GeoPackage gpkg {options.fileName};
    gpkg.addGeometryColumn(geopackage::GeometryColumn{
        options.tableName,
        options.columnName,
        geopackage::geometrytype::getGeometryType(options.geometryType),
        options.srsId,
        options.z,
        options.m
    });
}