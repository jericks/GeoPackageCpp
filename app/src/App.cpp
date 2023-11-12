#include <iostream>
#include "CLI/CLI.hpp"
#include "Commands.hpp"
#include "Command.hpp"
#include "ListCommand.hpp"
#include "CreateCommand.hpp"

#include "spatialref/CreateSpatialRefCommand.hpp"
#include "spatialref/DeleteSpatialRefCommand.hpp"
#include "spatialref/GetSpatialRefCommand.hpp"
#include "spatialref/ListSpatialRefCommand.hpp"

#include "content/CreateContentCommand.hpp"
#include "content/ListContentCommand.hpp"
#include "content/GetContentCommand.hpp"
#include "content/DeleteContentCommand.hpp"

#include "geometryColumn/ListGeometryColumnCommand.hpp"
#include "geometryColumn/GetGeometryColumnCommand.hpp"
#include "geometryColumn/DeleteGeometryColumnCommand.hpp"
#include "geometryColumn/CreateGeometryColumnCommand.hpp"

#include "extension/ListExtensionCommand.hpp"
#include "extension/GetExtensionCommand.hpp"
#include "extension/DeleteExtensionCommand.hpp"
#include "extension/CreateExtensionCommand.hpp"

#include "tileMatrixSet/ListTileMatrixSetCommand.hpp"
#include "tileMatrixSet/GetTileMatrixSetCommand.hpp"
#include "tileMatrixSet/CreateTileMatrixSetCommand.hpp"
#include "tileMatrixSet/DeleteTileMatrixSetCommand.hpp"

#include "tileMatrix/ListTileMatrixCommand.hpp"
#include "tileMatrix/GetTileMatrixCommand.hpp"
#include "tileMatrix/CreateTileMatrixCommand.hpp"
#include "tileMatrix/DeleteTileMatrixCommand.hpp"

#include "tile/CreateTileTableCommand.hpp"
#include "tile/ListTilesCommand.hpp"
#include "tile/GetTileCommand.hpp"
#include "tile/SetTileCommand.hpp"
#include "tile/DeleteTileCommand.hpp"
#include "tile/CreateGeodeticTileLayerCommand.hpp"
#include "tile/CreateMercatorTileLayerCommand.hpp"
#include "tile/ExportTilesCommand.hpp"
#include "tile/ImportTilesCommand.hpp"
#include "tile/InfoTileCommand.hpp"

#include "feature/RandomFeaturesCommand.hpp"
#include "feature/ListFeatureLayersCommand.hpp"
#include "feature/CountFeaturesCommand.hpp"
#include "feature/CreateFeatureLayerCommand.hpp"
#include "feature/InfoFeatureCommand.hpp"
#include "feature/AddFeatureCommand.hpp"
#include "feature/DeleteAllFeatureCommand.hpp"
#include "feature/DeleteFeatureCommand.hpp"
#include "feature/UpdateFeatureCommand.hpp"
#include "feature/GetFeatureCommand.hpp"
#include "feature/ListFeatureCommand.hpp"

#include "layerStyle/ListLayerStyleCommand.hpp"
#include "layerStyle/GetLayerStyleCommand.hpp"
#include "layerStyle/CreateLayerStyleCommand.hpp"
#include "layerStyle/DeleteLayerStyleCommand.hpp"

int main(int argc, char *argv[]) {

    CLI::App app{"GeoPackage CLI"};
    app.require_subcommand(1);

    Commands commands;
    
    ListCommand listCommand(&app, &commands);
    commands.add(&listCommand);

    CreateCommand createCommand(&app);
    commands.add(&createCommand);

    // SpatialRef

    CreateSpatialRefCommand createSpatialRefCommand(&app);
    commands.add(&createSpatialRefCommand);

    DeleteSpatialRefCommand deleteSpatialRefCommand(&app);
    commands.add(&deleteSpatialRefCommand);

    GetSpatialRefCommand getSpatialRefCommand(&app);
    commands.add(&getSpatialRefCommand);

    ListSpatialRefCommand listSpatialRefCommand(&app);
    commands.add(&listSpatialRefCommand);

    // Content

    CreateContentCommand createContentCommand(&app);
    commands.add(&createContentCommand);

    ListContentCommand listContentCommand(&app);
    commands.add(&listContentCommand);

    GetContentCommand getContentCommand(&app);
    commands.add(&getContentCommand);

    DeleteContentCommand deleteContentCommand(&app);
    commands.add(&deleteContentCommand);

    // Geometry Column

    ListGeometryColumnCommand listGeometryColumnCommand(&app);
    commands.add(&listGeometryColumnCommand);

    GetGeometryColumnCommand getGeometryColumnCommand(&app);
    commands.add(&getGeometryColumnCommand);

    CreateGeometryColumnCommand createGeometryColumnCommand(&app);
    commands.add(&createGeometryColumnCommand);

    DeleteGeometryColumnCommand deleteGeometryColumnCommand(&app);
    commands.add(&deleteGeometryColumnCommand);

    // Extenssion

    ListExtensionCommand listExtensionCommand(&app);
    commands.add(&listExtensionCommand);

    GetExtensionCommand getExtensionCommand(&app);
    commands.add(&getExtensionCommand);

    DeleteExtensionCommand deleteExtensionCommand(&app);
    commands.add(&deleteExtensionCommand);

    CreateExtensionCommand createExtensionCommand(&app);
    commands.add(&createExtensionCommand);

    // Tile Matrix Set

    ListTileMatrixSetCommand listTileMatrixSetCommand(&app);
    commands.add(&listTileMatrixSetCommand);

    GetTileMatrixSetCommand getTileMatrixSetCommand(&app);
    commands.add(&getTileMatrixSetCommand);

    CreateTileMatrixSetCommand createTileMatrixSetCommand(&app);
    commands.add(&createTileMatrixSetCommand);

    DeleteTileMatrixSetCommand deleteTileMatrixSetCommand(&app);
    commands.add(&deleteTileMatrixSetCommand);

    // Tile Matrix 

    ListTileMatrixCommand listTileMatrixCommand(&app);
    commands.add(&listTileMatrixCommand);

    GetTileMatrixCommand getTileMatrixCommand(&app);
    commands.add(&getTileMatrixCommand);

    CreateTileMatrixCommand createTileMatrixCommand(&app);
    commands.add(&createTileMatrixCommand);

    DeleteTileMatrixCommand deleteTileMatrixCommand(&app);
    commands.add(&deleteTileMatrixCommand);

    // Tile

    CreateTileTableCommand createTileTableCommand(&app);
    commands.add(&createTileTableCommand);

    ListTilesCommand listTilesCommand(&app);
    commands.add(&listTilesCommand);

    GetTileCommand getTileCommand(&app);
    commands.add(&getTileCommand);

    SetTileCommand setTileCommand(&app);
    commands.add(&setTileCommand);

    DeleteTileCommand deleteTileCommand(&app);
    commands.add(&deleteTileCommand);

    CreateGeodeticTileLayerCommand createGeodeticTileLayerCommand(&app);
    commands.add(&createGeodeticTileLayerCommand);

    CreateMercatorTileLayerCommand createMercatorTileLayerCommand(&app);
    commands.add(&createMercatorTileLayerCommand);

    ExportTilesCommand exportTilesCommand(&app);
    commands.add(&exportTilesCommand);

    ImportTilesCommand importTilesCommand(&app);
    commands.add(&importTilesCommand);

    InfoTileCommand infoTileCommand(&app);
    commands.add(&infoTileCommand);

    // Feature

    CreateFeatureLayerCommand createFeatureLayerCommand(&app);
    commands.add(&createFeatureLayerCommand);

    ListFeatureLayersCommand listFeatureLayersCommand(&app);
    commands.add(&listFeatureLayersCommand);

    RandomFeaturesCommand randomFeaturesCommand(&app);
    commands.add(&randomFeaturesCommand);

    CountFeaturesCommand countFeaturesCommand(&app);
    commands.add(&countFeaturesCommand);

    InfoFeatureCommand infoFeatureCommand(&app);
    commands.add(&infoFeatureCommand);

    AddFeatureCommand addFeatureCommand(&app);
    commands.add(&addFeatureCommand);

    DeleteAllFeatureCommand deleteAllFeatureCommand(&app);
    commands.add(&deleteAllFeatureCommand);

    DeleteFeatureCommand deleteFeatureCommand(&app);
    commands.add(&deleteFeatureCommand);

    UpdateFeatureCommand updateFeatureCommand(&app);
    commands.add(&updateFeatureCommand);

    GetFeatureCommand getFeatureCommand(&app);
    commands.add(&getFeatureCommand);

    ListFeatureCommand listFeatureCommand(&app);
    commands.add(&listFeatureCommand);

    // Layer Style

    ListLayerStyleCommand listLayerStyleCommand(&app);
    commands.add(&listLayerStyleCommand);

    GetLayerStyleCommand getLayerStyleCommand(&app);
    commands.add(&getLayerStyleCommand);

    CreateLayerStyleCommand createLayerStyleCommand(&app);
    commands.add(&createLayerStyleCommand);

    DeleteLayerStyleCommand deleteLayerStyleCommand(&app);
    commands.add(&deleteLayerStyleCommand);


    CLI11_PARSE(app, argc, argv);

    for(Command* cmd : commands.get()) {
      if (app.got_subcommand(cmd->getName())) {
        cmd->execute(std::cin, std::cout);
        break;
      }
    }

    return 0;

}