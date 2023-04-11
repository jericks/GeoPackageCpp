add_executable(cli_tests 
    ListCommandTest.cpp
    CreateCommandTest.cpp
    RandomFeaturesCommandtest.cpp
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
)
target_link_libraries(cli_tests 
    GeoPackageCppAppLib
    SQLiteCpp::SQLiteCpp
    CLI11::CLI11
    GTest::GTest
)
add_test(NAME "GeoPackageCliTests" COMMAND "cli_tests")