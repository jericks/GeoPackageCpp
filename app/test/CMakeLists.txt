add_executable(cli_tests 
    ListCommandTest.cpp
    CreateCommandTest.cpp
    RandomFeaturesCommandtest.cpp
    spatialref/CreateSpatialRefCommandTest.cpp
    spatialref/DeleteSpatialRefCommandTest.cpp
    spatialref/ListSpatialRefCommandTest.cpp
    spatialref/GetSpatialRefCommandTest.cpp
)
target_link_libraries(cli_tests 
    GeoPackageCppAppLib
    SQLiteCpp::SQLiteCpp
    CLI11::CLI11
    GTest::GTest
)
add_test(NAME "GeoPackageCliTests" COMMAND "cli_tests")