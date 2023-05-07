#include "tile/ListTilesCommand.hpp"

ListTilesCommand::ListTilesCommand(CLI::App* app): Command ("tile-list") {
    CLI::App* cmd = app->add_subcommand("tile-list", "List tile layers");
    cmd->add_option("-f", options.fileName, "File name")->required();
}

void ListTilesCommand::execute(std::istream& istream, std::ostream& ostream) {
    geopackage::GeoPackage gpkg {options.fileName};
    gpkg.contents(geopackage::DataType::TILES, [&](geopackage::Content& c) {
        ostream << c.getTableName() << "\n";
    });
}