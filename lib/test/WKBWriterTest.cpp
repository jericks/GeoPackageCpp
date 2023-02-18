#include <sstream>
#include <iostream>
#include <filesystem>
#include <fstream>
#include "gtest/gtest.h"
#include "WKBWriter.hpp"
#include "Point.hpp"
#include "LineString.hpp"
#include "Polygon.hpp"

// std::cout << "# of bytes = " << bytes.size() << "\n";
// std::ofstream outfile("point.wkb", std::ios::out | std::ios::binary);
// outfile.write(reinterpret_cast<const char*>(bytes.data()), bytes.size());

TEST(GeoPackageLibTests, WKBWrite_Point) {
    geopackage::WKBWriter writer{};
    geopackage::Point pt {2,4};
    std::string wkbHexString = writer.writeToHex(&pt);
    EXPECT_EQ("000000000140000000000000004010000000000000", wkbHexString);
}

TEST(GeoPackageLibTests, WKBWrite_LineString) {
    geopackage::WKBWriter writer{};
    geopackage::LineString line {{geopackage::Point {1,1}, geopackage::Point {5,5}}};
    std::string wkbHexString = writer.writeToHex(&line);
    EXPECT_EQ("0000000002000000023FF00000000000003FF000000000000040140000000000004014000000000000", wkbHexString);
}

TEST(GeoPackageLibTests, WKBWrite_Polygon) {
    geopackage::WKBWriter writer{};
    geopackage::LinearRing ring {{{0,0}, {0, 10}, {10,10}, {10, 0}, {0,0}}};
    geopackage::Polygon polygon {{ring}};
    std::string wkbHexString = writer.writeToHex(&polygon);
    EXPECT_EQ("000000000300000001000000050000000000000000000000000000000000000000000000004024000000000000402400000000000040240000000000004024000000000000000000000000000000000000000000000000000000000000", wkbHexString);
}

TEST(GeoPackageLibTests, WKBWrite_MultiPoint) {
    geopackage::WKBWriter writer{};
    geopackage::MultiPoint pts {{{4,5},{1,2},{6,7}}};
    std::string wkbHexString = writer.writeToHex(&pts);
    EXPECT_EQ("00000000040000000300000000014010000000000000401400000000000000000000013FF0000000000000400000000000000000000000014018000000000000401C000000000000", wkbHexString);
}

TEST(GeoPackageLibTests, WKBWrite_MultiLineString) {
    geopackage::WKBWriter writer{};
    geopackage::MultiLineString multiLine {{ 
        geopackage::LineString {{geopackage::Point {1,1}, geopackage::Point {5,5}}},
        geopackage::LineString {{geopackage::Point {2,2}, geopackage::Point {8,8}}}
    }};
    std::string wkbHexString = writer.writeToHex(&multiLine);
    EXPECT_EQ("0000000005000000020000000002000000023FF00000000000003FF0000000000000401400000000000040140000000000000000000002000000024000000000000000400000000000000040200000000000004020000000000000", wkbHexString);
}

TEST(GeoPackageLibTests, WKBWrite_MultiPolygon) {
    geopackage::WKBWriter writer{};
    geopackage::MultiPolygon multiPolygon {{ 
        geopackage::Polygon {{geopackage::LinearRing {{{0,0}, {0, 10}, {10,10}, {10, 0}, {0,0}}} }},
        geopackage::Polygon {{geopackage::LinearRing {{{20,20}, {20, 30}, {30,30}, {30, 20}, {20,20}}} }}
    }};
    std::string wkbHexString = writer.writeToHex(&multiPolygon);
    EXPECT_EQ("00000000060000000200000000030000000100000005000000000000000000000000000000000000000000000000402400000000000040240000000000004024000000000000402400000000000000000000000000000000000000000000000000000000000000000000030000000100000005403400000000000040340000000000004034000000000000403E000000000000403E000000000000403E000000000000403E000000000000403400000000000040340000000000004034000000000000", wkbHexString);
}

TEST(GeoPackageLibTests, WKBWrite_GeometryCollection) {
    geopackage::WKBWriter writer{};
    std::vector<std::unique_ptr<geopackage::Geometry>> geoms;
    geoms.push_back(geopackage::Point {4,5}.clone());
    geoms.push_back(geopackage::LineString {{geopackage::Point{1,1}, geopackage::Point{5,5}}}.clone());
    geopackage::GeometryCollection gc {std::move(geoms)};
    std::string wkbHexString = writer.writeToHex(&gc);
    EXPECT_EQ("0000000007000000020000000001401000000000000040140000000000000000000002000000023FF00000000000003FF000000000000040140000000000004014000000000000", wkbHexString);
}