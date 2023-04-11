project(GeoPackageCppApp)

add_library(GeoPackageCppAppLib STATIC
	src/Command.cpp
	src/Commands.cpp
	src/ListCommand.cpp
	src/CreateCommand.cpp
	# Feature
	src/RandomFeaturesCommand.cpp
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
)
target_include_directories(GeoPackageCppAppLib PUBLIC "include" "../lib/include" CLI11::CLI11)
target_compile_features(GeoPackageCppAppLib PUBLIC cxx_std_17)
target_link_libraries(GeoPackageCppAppLib PRIVATE GeoPackageCppLib SQLiteCpp::SQLiteCpp CLI11::CLI11)

# Application
add_executable(geopackage-cli src/App.cpp)
target_link_libraries(geopackage-cli PRIVATE GeoPackageCppAppLib GeoPackageCppLib SQLiteCpp::SQLiteCpp CLI11::CLI11) 

add_subdirectory(test)