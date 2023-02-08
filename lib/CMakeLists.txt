project(GeoPackageCppLib)

set(GeoPackageCppLib_SOURCES 
	src/GeoPackage.cpp
	src/Bounds.cpp
	src/Content.cpp
	src/DataType.cpp
	src/Extension.cpp
	src/Scope.cpp
	src/SpatialRef.cpp
	src/Tile.cpp
	src/TileMatrix.cpp
	src/TileMatrixSet.cpp
)

add_library(GeoPackageCppLib STATIC ${GeoPackageCppLib_SOURCES})

target_include_directories(GeoPackageCppLib
	PUBLIC include SQLiteCpp::SQLiteCpp
	PRIVATE src
)
target_link_libraries(GeoPackageCppLib SQLiteCpp::SQLiteCpp)

add_subdirectory(test)