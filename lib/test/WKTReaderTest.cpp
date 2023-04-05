#include <sstream>
#include <iostream>
#include <filesystem>
#include <fstream>
#include "gtest/gtest.h"
#include "WKTReader.hpp"
#include "Point.hpp"
#include "LineString.hpp"
#include "Polygon.hpp"

#include <ctime>

TEST(WKTReaderTests, ReadPoint) {
    geopackage::WKTReader reader{};
    std::unique_ptr<geopackage::Geometry> g = reader.read("POINT (1 1)");
    EXPECT_EQ("POINT (1 1)", g->wkt());
}

TEST(WKTReaderTests, ReadLineString) {
    geopackage::WKTReader reader{};
    std::unique_ptr<geopackage::Geometry> g = reader.read("LINESTRING (1 1, 2 2)");
    EXPECT_EQ("LINESTRING (1 1, 2 2)", g->wkt());
}

TEST(WKTReaderTests, ReadPolygon) {
    geopackage::WKTReader reader{};
    std::unique_ptr<geopackage::Geometry> g = reader.read("POLYGON ((0 0, 0 10, 10 10, 10 0, 0 0))");
    EXPECT_EQ("POLYGON ((0 0, 0 10, 10 10, 10 0, 0 0))", g->wkt());
}

TEST(WKTReaderTests, ReadMultiPoint) {
    geopackage::WKTReader reader{};
    std::unique_ptr<geopackage::Geometry> g = reader.read("MULTIPOINT (4 5, 1 2, 6 7)");
    EXPECT_EQ("MULTIPOINT (4 5, 1 2, 6 7)", g->wkt());
}

TEST(WKTReaderTests, ReadMultiPointAlt) {
    geopackage::WKTReader reader{};
    std::unique_ptr<geopackage::Geometry> g = reader.read("MULTIPOINT ((4 5), (1 2), (6 7))");
    EXPECT_EQ("MULTIPOINT (4 5, 1 2, 6 7)", g->wkt());
}

TEST(WKTReaderTests, ReadMultiLineString) {
    geopackage::WKTReader reader{};
    std::unique_ptr<geopackage::Geometry> g = reader.read("MULTILINESTRING ((1 1, 5 5), (2 2, 8 8))");
    EXPECT_EQ("MULTILINESTRING ((1 1, 5 5), (2 2, 8 8))", g->wkt());
}

TEST(WKTReaderTests, ReadMultiPolygon) {
    geopackage::WKTReader reader{};
    std::unique_ptr<geopackage::Geometry> g = reader.read("MULTIPOLYGON (((0 0, 0 10, 10 10, 10 0, 0 0)), ((20 20, 20 30, 30 30, 30 20, 20 20)))");
    EXPECT_EQ("MULTIPOLYGON (((0 0, 0 10, 10 10, 10 0, 0 0)), ((20 20, 20 30, 30 30, 30 20, 20 20)))", g->wkt());
}

TEST(WKTReaderTests, ReadGeometryCollection) {
    geopackage::WKTReader reader{};
    std::unique_ptr<geopackage::Geometry> g = reader.read("GEOMETRYCOLLECTION (POINT (4 5), LINESTRING (1 1, 5 5))");
    EXPECT_EQ("GEOMETRYCOLLECTION (POINT (4 5), LINESTRING (1 1, 5 5))", g->wkt());
}
TEST(WKTReaderTests, ReadGeometryCollectionNested) {
    geopackage::WKTReader reader{};
    std::unique_ptr<geopackage::Geometry> g = reader.read("GEOMETRYCOLLECTION (POINT (4 5), LINESTRING (1 1, 5 5), GEOMETRYCOLLECTION (POINT (44 55), LINESTRING (11 11, 55 55)) )");
    EXPECT_EQ("GEOMETRYCOLLECTION (POINT (4 5), LINESTRING (1 1, 5 5), GEOMETRYCOLLECTION (POINT (44 55), LINESTRING (11 11, 55 55)))", g->wkt());    
}