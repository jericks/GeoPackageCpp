add_executable(tests 
    GeoPackageTest.cpp
)
target_link_libraries(tests 
    GeoPackageCppLib
    GTest::GTest
)
add_test(NAME "GeoPackageTests" COMMAND "tests")