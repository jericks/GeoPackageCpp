project(GeoPackageCppLib)

set(GeoPackageCppLib_SOURCES 
	src/GeoPackage.cpp
	src/Bytes.cpp
	src/GeoPackageGeometryWriter.cpp
	src/GeoPackageGeometryReader.cpp
	src/BinaryType.cpp
	src/EnvelopeType.cpp
	src/Flag.cpp
	src/Bounds.cpp
	src/Content.cpp
	src/DataType.cpp
	src/Dimension
	src/Extension.cpp
	src/Feature.cpp
	src/Field.cpp
	src/FieldType.cpp
	src/Geometry.cpp
	src/GeometryColumn.cpp
	src/GeometryCollection.cpp
	src/GeometryField.cpp
	src/GeometryType.cpp
	src/LineString.cpp
	src/LinearRing.cpp
	src/MultiLineString.cpp
	src/MultiPoint.cpp
	src/MultiPolygon.cpp
	src/Point.cpp
	src/Polygon.cpp
	src/Schema.cpp
	src/Scope.cpp
	src/Size.cpp
	src/SpatialRef.cpp
	src/Tile.cpp
	src/TileMatrix.cpp
	src/TileMatrixSet.cpp
	src/WKBWriter.cpp
	src/WKBReader.cpp
	src/WKTReader.cpp
	src/WKTWriter.cpp
)

add_library(GeoPackageCppLib STATIC ${GeoPackageCppLib_SOURCES})

target_include_directories(GeoPackageCppLib
	PUBLIC include SQLiteCpp::SQLiteCpp
	PRIVATE src
)
target_link_libraries(GeoPackageCppLib SQLiteCpp::SQLiteCpp cpp-peglib::cpp-peglib)

add_subdirectory(test)