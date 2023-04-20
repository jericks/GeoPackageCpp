#include <sstream>
#include <iostream>
#include <filesystem>
#include <fstream>
#include "gtest/gtest.h"
#include "WKTWriter.hpp"
#include "Point.hpp"
#include "LineString.hpp"
#include "Polygon.hpp"
#include "MultiPoint.hpp"
#include "MultiLineString.hpp"
#include "MultiPolygon.hpp"
#include "GeometryCollection.hpp"

TEST(WKTWriter, Point) {
    geopackage::WKTWriter writer{};
    geopackage::Point pt {2,4};
    std::string wkt = writer.write(&pt);
    EXPECT_EQ("POINT (2 4)", wkt);
}

TEST(WKTWriter, LineString) {
    geopackage::WKTWriter writer{};
    geopackage::LineString line {{geopackage::Point {1,1}, geopackage::Point {5,5}}};
    std::string wkt = writer.write(&line);
    ASSERT_EQ("LINESTRING (1 1, 5 5)", wkt);
}

TEST(WKTWriter, Polygon) {
    geopackage::WKTWriter writer{};
    geopackage::LinearRing ring {{{0,0}, {0, 10}, {10,10}, {10, 0}, {0,0}}};
    geopackage::Polygon polygon {{ring}};
    std::string wkt = writer.write(&polygon);
    ASSERT_EQ("POLYGON ((0 0, 0 10, 10 10, 10 0, 0 0))", wkt);
}

TEST(WKTWriter, MultiPoint) {
    geopackage::WKTWriter writer{};
    geopackage::MultiPoint pts {{{4,5},{1,2},{6,7}}};
    std::string wkt = writer.write(&pts);
    EXPECT_EQ("MULTIPOINT (4 5, 1 2, 6 7)", wkt);
}

TEST(WKTWriter, MultiLineString) {
    geopackage::WKTWriter writer{};
    geopackage::MultiLineString multiLine {{ 
        geopackage::LineString {{geopackage::Point {1,1}, geopackage::Point {5,5}}},
        geopackage::LineString {{geopackage::Point {2,2}, geopackage::Point {8,8}}}
    }};
    std::string wkt = writer.write(&multiLine);
    ASSERT_EQ("MULTILINESTRING ((1 1, 5 5), (2 2, 8 8))", wkt);
}

TEST(WKTWriter, MultiPolygon) {
    geopackage::WKTWriter writer{};
    geopackage::MultiPolygon multiPolygon {{ 
        geopackage::Polygon {{geopackage::LinearRing {{{0,0}, {0, 10}, {10,10}, {10, 0}, {0,0}}} }},
        geopackage::Polygon {{geopackage::LinearRing {{{20,20}, {20, 30}, {30,30}, {30, 20}, {20,20}}} }}
    }};
    std::string wkt = writer.write(&multiPolygon);
    ASSERT_EQ("MULTIPOLYGON (((0 0, 0 10, 10 10, 10 0, 0 0)), ((20 20, 20 30, 30 30, 30 20, 20 20)))", wkt);
}

TEST(WKTWriter, GeometryCollection) {
    geopackage::WKTWriter writer{};
    std::vector<std::unique_ptr<geopackage::Geometry>> geoms;
    geoms.push_back(geopackage::Point {4,5}.clone());
    geoms.push_back(geopackage::LineString {{geopackage::Point{1,1}, geopackage::Point{5,5}}}.clone());
    geopackage::GeometryCollection gc {std::move(geoms)};
    std::string wkt = writer.write(&gc);
    ASSERT_EQ("GEOMETRYCOLLECTION (POINT (4 5), LINESTRING (1 1, 5 5))", wkt);
}