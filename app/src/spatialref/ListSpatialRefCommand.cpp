#include "spatialref/ListSpatialRefCommand.hpp"

ListSpatialRefCommand::ListSpatialRefCommand(CLI::App* app): Command ("spatialref-list") {
    CLI::App* cmd = app->add_subcommand("spatialref-list", "List spatial references");
    cmd->add_option("-f", options.fileName, "File")->required();
}

void ListSpatialRefCommand::execute(std::istream& istream, std::ostream& ostream) {
    geopackage::GeoPackage gpkg {options.fileName};
    gpkg.spatialRefs([&](geopackage::SpatialRef& s) {
        ostream << "SRS ID: " << s.getSrsId() << "\n";
        ostream << "Name: " << s.getSrsName() << "\n";
        ostream << "Organization: " << s.getOrganization() << "\n";
        ostream << "Organization Coord Sys Id: " << s.getOrganizationCoordSysId() << "\n";
        ostream << "Description: " << s.getDescription() << "\n";
        ostream << "Definition: " << s.getDefinition() << "\n";
        ostream << "\n";
    });
}