#include "geometryColumn/ListGeometryColumnCommand.hpp"

ListGeometryColumnCommand::ListGeometryColumnCommand(CLI::App* app): Command ("geometrycolumn-list") {
    CLI::App* cmd = app->add_subcommand("geometrycolumn-list", "List GeometryColumn entries");
    cmd->add_option("-f", options.fileName, "File")->required();
}

void ListGeometryColumnCommand::execute(std::istream& istream, std::ostream& ostream) {
    geopackage::GeoPackage gpkg {options.fileName};
    gpkg.geometryColumns([&](geopackage::GeometryColumn& c) {
        ostream << "Name: " << c.getTableName() << "\n";
        ostream << "Column: " << c.getColumnName() << "\n";
        ostream << "Geometry Type: " << geopackage::geometrytype::toString(c.getGeometryType()) << "\n";
        ostream << "SRS ID: " << c.getSrsId() << "\n";
        ostream << "Has Z: " << (c.hasZ() ? "true" : "false") << "\n";
        ostream << "Has M: " << (c.hasM() ? "true" : "false") << "\n";
        ostream << "\n";
    });
}