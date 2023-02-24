#include <sstream>
#include <iostream>
#include <filesystem>
#include <fstream>
#include "gtest/gtest.h"
#include "GeoPackageGeometryWriter.hpp"
#include "Point.hpp"

TEST(GeoPackageLibTests, GeoPackageGeometryWriter_Point) {
    geopackage::GeoPackageGeometryWriter writer{};
    geopackage::Point pt {31.19999710971274, -26.466667461352472};
    pt.setSrid("4326");
    std::string wkbHexString = writer.writeToHex(&pt);
    EXPECT_EQ("47500002000010E6403F333302B582C0403F333302B582C0C03A777784CC9DC0C03A777784CC9DC00020000001000010E6403F333302B582C0C03A777784CC9DC0", wkbHexString);
}