project(GeoPackageCppApp)

add_library(GeoPackageCppAppLib STATIC
	src/Command.cpp
	src/Commands.cpp
	src/ListCommand.cpp
	src/CreateCommand.cpp
	# Content
	src/content/CreateContentCommand.cpp
	src/content/ListContentCommand.cpp
	src/content/GetContentCommand.cpp
	src/content/DeleteContentCommand.cpp
	# Spatial Reference
	src/spatialref/CreateSpatialRefCommand.cpp
	src/spatialref/DeleteSpatialRefCommand.cpp
	src/spatialref/ListSpatialRefCommand.cpp
	src/spatialref/GetSpatialRefCommand.cpp
	# Geometry Column
	src/geometryColumn/ListGeometryColumnCommand.cpp
	src/geometryColumn/GetGeometryColumnCommand.cpp
	src/geometryColumn/DeleteGeometryColumnCommand.cpp
	src/geometryColumn/CreateGeometryColumnCommand.cpp
	# Extension
	src/extension/ListExtensionCommand.cpp
	src/extension/GetExtensionCommand.cpp
	src/extension/DeleteExtensionCommand.cpp
	src/extension/CreateExtensionCommand.cpp
	# TileMatrixSet
	src/tileMatrixSet/ListTileMatrixSetCommand.cpp
	src/tileMatrixSet/GetTileMatrixSetCommand.cpp
	src/tileMatrixSet/CreateTileMatrixSetCommand.cpp
	src/tileMatrixSet/DeleteTileMatrixSetCommand.cpp
	# TileMatrix
	src/tileMatrix/ListTileMatrixCommand.cpp
	src/tileMatrix/GetTileMatrixCommand.cpp
	src/tileMatrix/CreateTileMatrixCommand.cpp
	src/tileMatrix/DeleteTileMatrixCommand.cpp
	# Tile
	src/tile/CreateTileTableCommand.cpp
	src/tile/ListTilesCommand.cpp
	src/tile/GetTileCommand.cpp
	src/tile/SetTileCommand.cpp
	src/tile/DeleteTileCommand.cpp
	src/tile/CreateGeodeticTileLayerCommand.cpp
	src/tile/CreateMercatorTileLayerCommand.cpp
	src/tile/ExportTilesCommand.cpp
	src/tile/ImportTilesCommand.cpp
	src/tile/InfoTileCommand.cpp
	# Feature
	src/feature/RandomFeaturesCommand.cpp
	src/feature/ListFeatureLayersCommand.cpp
	src/feature/CountFeaturesCommand.cpp
	src/feature/CreateFeatureLayerCommand.cpp
	src/feature/InfoFeatureCommand.cpp
	src/feature/AddFeatureCommand.cpp
)
target_include_directories(GeoPackageCppAppLib 
	PUBLIC "include" "../lib/include" 
	PUBLIC CLI11::CLI11 cpp-peglib::cpp-peglib
)
target_compile_features(GeoPackageCppAppLib PUBLIC cxx_std_17)
target_link_libraries(GeoPackageCppAppLib PUBLIC GeoPackageCppLib SQLiteCpp::SQLiteCpp CLI11::CLI11 cpp-peglib::cpp-peglib)

# Application
add_executable(geopackage-cli src/App.cpp)
target_link_libraries(geopackage-cli PUBLIC GeoPackageCppAppLib GeoPackageCppLib SQLiteCpp::SQLiteCpp CLI11::CLI11 cpp-peglib::cpp-peglib) 

add_subdirectory(test)