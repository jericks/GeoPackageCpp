#include "geometryColumn/DeleteGeometryColumnCommand.hpp"

DeleteGeometryColumnCommand::DeleteGeometryColumnCommand(CLI::App* app): Command ("geometrycolumn-delete") {
    CLI::App* cmd = app->add_subcommand("geometrycolumn-delete", "Delete a Geometry Column by name");
    cmd->add_option("-f", options.fileName, "File")->required();
    cmd->add_option("-n", options.name, "Name")->required();
}

void DeleteGeometryColumnCommand::execute(std::istream& istream, std::ostream& ostream) {
    geopackage::GeoPackage gpkg {options.fileName};
    auto geometryColumn = gpkg.getGeometryColumn(options.name);
    if (geometryColumn.has_value()) {
        auto gc = geometryColumn.value();
        gpkg.deleteGeometryColumn(gc);
    }
}