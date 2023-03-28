#include "spatialref/CreateSpatialRefCommand.hpp"

CreateSpatialRefCommand::CreateSpatialRefCommand(CLI::App* app): Command ("spatialref-create") {
    CLI::App* cmd = app->add_subcommand("spatialref-create", "Create a spatial reference");
    cmd->add_option("-f", options.fileName, "File")->required();
    cmd->add_option("-n", options.srsName, "SRS Name")->required();
    cmd->add_option("-s", options.srsId, "SRS ID")->required();
    cmd->add_option("-o", options.organization, "Organization")->required();
    cmd->add_option("-i", options.organizationCoordSysId, "Organization Coordinate System ID")->required();
    cmd->add_option("-d", options.definition, "Definition")->required();
    cmd->add_option("-c", options.description, "Description")->required();
}

void CreateSpatialRefCommand::execute(std::istream& istream, std::ostream& ostream) {
    geopackage::GeoPackage gpkg {options.fileName};
    gpkg.addSpatialRef(geopackage::SpatialRef{
        options.srsName,
        options.srsId,
        options.organization,
        options.organizationCoordSysId,
        options.definition,
        options.description
    });
}