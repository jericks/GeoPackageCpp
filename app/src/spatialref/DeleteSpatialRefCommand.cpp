#include "spatialref/DeleteSpatialRefCommand.hpp"

DeleteSpatialRefCommand::DeleteSpatialRefCommand(CLI::App* app): Command ("spatialref-delete") {
    CLI::App* cmd = app->add_subcommand("spatialref-delete", "Delete spatial reference by SRS ID");
    cmd->add_option("-f", options.fileName, "File")->required();
    cmd->add_option("-s", options.srsId, "SRS ID")->required();
}

void DeleteSpatialRefCommand::execute(std::istream& istream, std::ostream& ostream) {
    geopackage::GeoPackage gpkg {options.fileName};
    auto spatialRef = gpkg.getSpatialRef(options.srsId);
    if (spatialRef.has_value()) {
        auto s = spatialRef.value();
        gpkg.deleteSpatialRef(s);
    }
}