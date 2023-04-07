#include "geometryColumn/GetGeometryColumnCommand.hpp"

GetGeometryColumnCommand::GetGeometryColumnCommand(CLI::App* app): Command ("geometrycolumn-get") {
    CLI::App* cmd = app->add_subcommand("geometrycolumn-get", "Get GeometryColumn by name");
    cmd->add_option("-f", options.fileName, "File")->required();
    cmd->add_option("-n", options.name, "Name")->required();
}

void GetGeometryColumnCommand::execute(std::istream& istream, std::ostream& ostream) {
    geopackage::GeoPackage gpkg {options.fileName};
    auto geometryColumn = gpkg.getGeometryColumn(options.name);
    if (geometryColumn.has_value()) {
        ostream << "Name: " << geometryColumn->getTableName() << "\n";
        ostream << "Column: " << geometryColumn->getColumnName() << "\n";
        ostream << "Geometry Type: " << geopackage::geometrytype::toString(geometryColumn->getGeometryType()) << "\n";
        ostream << "SRS ID: " << geometryColumn->getSrsId() << "\n";
        ostream << "Has Z: " << (geometryColumn->hasZ() ? "true" : "false") << "\n";
        ostream << "Has M: " << (geometryColumn->hasM() ? "true" : "false") << "\n";
        ostream << "\n";
    }
}