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

TEST(GeoPackageLibTests, GeoPackageGeometryWriter_LineString) {
    geopackage::GeoPackageGeometryWriter writer{};
    geopackage::LineString line {{geopackage::Point {1,1}, geopackage::Point {5,5}}};
    line.setSrid("4326");
    std::string wkbHexString = writer.writeToHex(&line);
    EXPECT_EQ("47500002000010E63FF000000000000040140000000000003FF000000000000040140000000000000020000002000010E6000000023FF00000000000003FF000000000000040140000000000004014000000000000", wkbHexString);
}

TEST(GeoPackageLibTests, GeoPackageGeometryWriter_Polygon) {
    geopackage::GeoPackageGeometryWriter writer{};
    geopackage::LinearRing ring {{{0,0}, {0, 10}, {10,10}, {10, 0}, {0,0}}};
    geopackage::Polygon polygon {{ring}};
    polygon.setSrid("4326");
    std::string wkbHexString = writer.writeToHex(&polygon);
    EXPECT_EQ("47500002000010E600000000000000004024000000000000000000000000000040240000000000000020000003000010E600000001000000050000000000000000000000000000000000000000000000004024000000000000402400000000000040240000000000004024000000000000000000000000000000000000000000000000000000000000", wkbHexString);
}

TEST(GeoPackageLibTests, GeoPackageGeometryWriter_MultiPoint) {
    geopackage::GeoPackageGeometryWriter writer{};
    geopackage::MultiPoint pts {{{4,5},{1,2},{6,7}}};
    pts.setSrid("4326");
    std::string wkbHexString = writer.writeToHex(&pts);
    EXPECT_EQ("47500002000010E63FF000000000000040180000000000004000000000000000401C0000000000000020000004000010E60000000300000000014010000000000000401400000000000000000000013FF0000000000000400000000000000000000000014018000000000000401C000000000000", wkbHexString);
}

TEST(GeoPackageLibTests, GeoPackageGeometryWriter_MultiLineString) {
    geopackage::GeoPackageGeometryWriter writer{};
    geopackage::MultiLineString multiLine {{ 
        geopackage::LineString {{geopackage::Point {1,1}, geopackage::Point {5,5}}},
        geopackage::LineString {{geopackage::Point {2,2}, geopackage::Point {8,8}}}
    }};
    multiLine.setSrid("4326");
    std::string wkbHexString = writer.writeToHex(&multiLine);
    EXPECT_EQ("47500002000010E63FF000000000000040200000000000003FF000000000000040200000000000000020000005000010E6000000020000000002000000023FF00000000000003FF0000000000000401400000000000040140000000000000000000002000000024000000000000000400000000000000040200000000000004020000000000000", wkbHexString);
}

TEST(GeoPackageLibTests, GeoPackageGeometryWriter_MultiPolygon) {
    geopackage::GeoPackageGeometryWriter writer{};
    geopackage::MultiPolygon multiPolygon {{ 
        geopackage::Polygon {{geopackage::LinearRing {{{0,0}, {0, 10}, {10,10}, {10, 0}, {0,0}}} }},
        geopackage::Polygon {{geopackage::LinearRing {{{20,20}, {20, 30}, {30,30}, {30, 20}, {20,20}}} }}
    }};
    multiPolygon.setSrid("4326");
    std::string wkbHexString = writer.writeToHex(&multiPolygon);
    EXPECT_EQ("47500002000010E60000000000000000403E0000000000000000000000000000403E0000000000000020000006000010E60000000200000000030000000100000005000000000000000000000000000000000000000000000000402400000000000040240000000000004024000000000000402400000000000000000000000000000000000000000000000000000000000000000000030000000100000005403400000000000040340000000000004034000000000000403E000000000000403E000000000000403E000000000000403E000000000000403400000000000040340000000000004034000000000000", wkbHexString);
}

TEST(GeoPackageLibTests, GeoPackageGeometryWriter_GeometryCollection) {
    geopackage::GeoPackageGeometryWriter writer{};
    std::vector<std::unique_ptr<geopackage::Geometry>> geoms;
    geoms.push_back(geopackage::Point {4,5}.clone());
    geoms.push_back(geopackage::LineString {{geopackage::Point{1,1}, geopackage::Point{5,5}}}.clone());
    geopackage::GeometryCollection gc {std::move(geoms)};
    gc.setSrid("4326");
    std::string wkbHexString = writer.writeToHex(&gc);
    EXPECT_EQ("47500002000010E63FF000000000000040140000000000003FF000000000000040140000000000000020000007000010E6000000020000000001401000000000000040140000000000000000000002000000023FF00000000000003FF000000000000040140000000000004014000000000000", wkbHexString);
}