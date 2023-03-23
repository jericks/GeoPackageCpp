add_executable(cli_tests 
    ListCommandTest.cpp
    CreateCommandTest.cpp
    CreateSpatialRefCommandTest.cpp
    ListSpatialRefCommandTest.cpp
    GetSpatialRefCommandTest.cpp
    RandomFeaturesCommandtest.cpp
)
target_link_libraries(cli_tests 
    GeoPackageCppAppLib
    SQLiteCpp::SQLiteCpp
    CLI11::CLI11
    GTest::GTest
)
add_test(NAME "GeoPackageCliTests" COMMAND "cli_tests")