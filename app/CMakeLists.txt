project(GeoPackageCppApp)

add_library(GeoPackageCppAppLib STATIC
	src/Command.cpp
	src/Commands.cpp
	src/ListCommand.cpp
	src/CreateCommand.cpp
	src/RandomFeaturesCommand.cpp
)
target_include_directories(GeoPackageCppAppLib PUBLIC "include" "../lib/include" CLI11::CLI11)
target_compile_features(GeoPackageCppAppLib PUBLIC cxx_std_17)
target_link_libraries(GeoPackageCppAppLib PRIVATE GeoPackageCppLib SQLiteCpp::SQLiteCpp CLI11::CLI11)

# Application
add_executable(geopackage-cli src/App.cpp)
target_link_libraries(geopackage-cli PRIVATE GeoPackageCppAppLib GeoPackageCppLib SQLiteCpp::SQLiteCpp CLI11::CLI11) 

add_subdirectory(test)