add_executable(cli_tests 
    ListCommandTest.cpp
    CreateCommandTest.cpp
    # Content
    content/CreateContentCommandTest.cpp
    content/ListContentCommandTest.cpp
    content/GetContentCommandTest.cpp
    content/DeleteContentCommandTest.cpp
    # Spatial Reference
    spatialref/CreateSpatialRefCommandTest.cpp
    spatialref/DeleteSpatialRefCommandTest.cpp
    spatialref/ListSpatialRefCommandTest.cpp
    spatialref/GetSpatialRefCommandTest.cpp
    # Geometry Column
    geometryColumn/ListGeometryColumnCommandTest.cpp
    geometryColumn/GetGeometryColumnCommandTest.cpp
    geometryColumn/DeleteGeometryColumnCommandTest.cpp
    geometryColumn/CreateGeometryColumnCommandTest.cpp
    # Extension
    extension/ListExtensionCommandTest.cpp
    extension/GetExtensionCommandTest.cpp
    extension/DeleteExtensionCommandTest.cpp
    extension/CreateExtensionCommandTest.cpp
    # Tile Matrix Set
    tileMatrixSet/ListTileMatrixSetCommandTest.cpp
    tileMatrixSet/GetTileMatrixSetCommandTest.cpp
    tileMatrixSet/CreateTileMatrixSetCommandTest.cpp
    tileMatrixSet/DeleteTileMatrixSetCommandTest.cpp
    # Tile Matrix
    tileMatrix/ListTileMatrixCommandTest.cpp
    tileMatrix/GetTileMatrixCommandTest.cpp
    tileMatrix/CreateTileMatrixCommandTest.cpp
    tileMatrix/DeleteTileMatrixCommandTest.cpp
    # Tile
    tile/CreateTileTableCommandTest.cpp
    tile/ListTilesCommandTest.cpp
    tile/GetTileCommandTest.cpp
    tile/SetTileCommandTest.cpp
    tile/DeleteTileCommandTest.cpp
    tile/CreateMercatorTileLayerCommandTest.cpp
    tile/CreateGeodeticTileLayerCommandTest.cpp
    tile/ExportTilesCommandTest.cpp
    tile/ImportTilesCommandTest.cpp
    tile/InfoTileCommandTest.cpp
    # Feature
    feature/ListFeatureLayersCommandTest.cpp
    feature/RandomFeaturesCommandTest.cpp
    feature/CountFeaturesCommandTest.cpp
    feature/CreateFeatureLayerCommandTest.cpp
    feature/InfoFeatureCommandTest.cpp
    feature/AddFeatureCommandTest.cpp
    feature/DeleteAllFeatureCommandTest.cpp
    feature/DeleteFeatureCommandTest.cpp
    feature/UpdateFeatureCommandTest.cpp
    feature/GetFeatureCommandTest.cpp
    feature/ListFeatureCommandTest.cpp
    # LayerStyle
    layerStyle/ListLayerStyleCommandTest.cpp
)   
target_link_libraries(cli_tests 
    GeoPackageCppAppLib
    SQLiteCpp::SQLiteCpp
    CLI11::CLI11
    GTest::GTest
)
add_test(NAME "GeoPackageCliTests" COMMAND "cli_tests")