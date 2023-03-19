#include "GetSpatialRefCommand.hpp"

GetSpatialRefCommand::GetSpatialRefCommand(CLI::App* app): Command ("spatialref-get") {
    CLI::App* cmd = app->add_subcommand("spatialref-get", "Get spatial reference by SRS ID");
    cmd->add_option("-f", options.fileName, "File")->required();
    cmd->add_option("-s", options.srsId, "SRS ID")->required();
    cmd->add_option("-a", options.all, "Display all information, not just definition");
}

void GetSpatialRefCommand::execute(std::istream& istream, std::ostream& ostream) {
    geopackage::GeoPackage gpkg {options.fileName};
    auto spatialRef = gpkg.getSpatialRef(options.srsId);
    if (spatialRef.has_value()) {
        auto s = spatialRef.value();
        if (options.all) {
            ostream << "SRS ID: " << s.getSrsId() << "\n";
            ostream << "Name: " << s.getSrsName() << "\n";
            ostream << "Organization: " << s.getOrganization() << "\n";
            ostream << "Organization Coord Sys Id: " << s.getOrganizationCoordSysId() << "\n";
            ostream << "Description: " << s.getDescription() << "\n";
            ostream << "Definition: " << s.getDefinition() << "\n";
        } else {
            ostream << s.getDefinition() << "\n";
        }
    }
}