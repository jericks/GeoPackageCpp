#include "tile/InfoTileCommand.hpp"

InfoTileCommand::InfoTileCommand(CLI::App* app): Command ("tile-info") {
    CLI::App* cmd = app->add_subcommand("tile-info", "Get information on tiles");
    cmd->add_option("-f", options.fileName, "File")->required();
    cmd->add_option("-n", options.tableName, " Name")->required();
}

void InfoTileCommand::execute(std::istream& istream, std::ostream& ostream) {
    geopackage::GeoPackage gpkg {options.fileName};
    auto content = gpkg.getContent(options.tableName);
    if (content) {
        ostream << "Information" << "\n";
        ostream << "Name: " << content->getTableName() << "\n";
        ostream << "Description: " << content->getDescription() << "\n";
        ostream << "SRS ID: " << content->getSrsId() << "\n";
        ostream << "Bounds: " << content->getBounds() << "\n";
        ostream << "\n" << "Tiles" << "\n";
        for(int z = gpkg.getMinZoom(options.tableName); z <= gpkg.getMaxZoom(options.tableName); ++z) {
            ostream << z << " = " << gpkg.countTiles(options.tableName, z) << "\n";    
        }
    }
}