#include <sstream>
#include <iostream>
#include <filesystem>
#include <fstream>
#include "gtest/gtest.h"
#include "Bytes.hpp"
#include "WKBReader.hpp"
#include "WKBWriter.hpp"
#include "Point.hpp"
#include "LineString.hpp"
#include "Polygon.hpp"

TEST(GeoPackageLibTests, WKBReader_Point_XY) {
    geopackage::WKBReader reader{};
    geopackage::Bytes bytes = geopackage::Bytes::fromHexString(geopackage::Endian::BIG, "000000000140000000000000004010000000000000");
    std::unique_ptr<geopackage::Geometry> geometry = reader.read(bytes.getBytes());
    EXPECT_EQ("POINT (2 4)", geometry->wkt());
}

TEST(GeoPackageLibTests, WKBReader_Point_XY_Srid) {
    geopackage::WKBReader reader{};
    geopackage::Bytes bytes = geopackage::Bytes::fromHexString(geopackage::Endian::BIG, "0020000001000010E640000000000000004010000000000000");
    std::unique_ptr<geopackage::Geometry> geometry = reader.read(bytes.getBytes());
    EXPECT_EQ("POINT (2 4)", geometry->wkt());
    EXPECT_EQ("4326", geometry->getSrid());
}

TEST(GeoPackageLibTests, WKBReader_Point_XYZM_Srid) {
    geopackage::WKBWriter writer{geopackage::wkb::Type::EWKB, geopackage::Endian::BIG};
    geopackage::Point point{-123.21, 47.34, 120.12, 5.6};
    point.setSrid("4326");
    std::string wkbHexString = writer.writeToHex(&point);
    geopackage::WKBReader reader{};
    geopackage::Bytes bytes = geopackage::Bytes::fromHexString(geopackage::Endian::BIG, wkbHexString);
    std::unique_ptr<geopackage::Geometry> geometry = reader.read(bytes.getBytes());
    EXPECT_EQ("POINT ZM (-123.21 47.34 120.12 5.6)", geometry->wkt());
    EXPECT_EQ("4326", geometry->getSrid());
}

TEST(GeoPackageLibTests, WKBReader_LineString_XY) {
    geopackage::WKBWriter writer{geopackage::wkb::Type::EWKB, geopackage::Endian::BIG};
    geopackage::LineString line {{geopackage::Point {1,1}, geopackage::Point {5,5}}};
    std::string wkbHexString = writer.writeToHex(&line);
    geopackage::WKBReader reader{};
    geopackage::Bytes bytes = geopackage::Bytes::fromHexString(geopackage::Endian::BIG, wkbHexString);
    std::unique_ptr<geopackage::Geometry> geometry = reader.read(bytes.getBytes());
    EXPECT_EQ("LINESTRING (1 1, 5 5)", geometry->wkt());
    EXPECT_EQ("", geometry->getSrid());
}

TEST(GeoPackageLibTests, WKBReader_LineString_XY_SRID) {
    geopackage::WKBWriter writer{geopackage::wkb::Type::EWKB, geopackage::Endian::BIG};
    geopackage::LineString line {{geopackage::Point {1,1}, geopackage::Point {5,5}}};
    line.setSrid("4326");
    std::string wkbHexString = writer.writeToHex(&line);
    geopackage::WKBReader reader{};
    geopackage::Bytes bytes = geopackage::Bytes::fromHexString(geopackage::Endian::BIG, wkbHexString);
    std::unique_ptr<geopackage::Geometry> geometry = reader.read(bytes.getBytes());
    EXPECT_EQ("LINESTRING (1 1, 5 5)", geometry->wkt());
    EXPECT_EQ("4326", geometry->getSrid());
}

TEST(GeoPackageLibTests, WKBReader_Polygon_XY_SRID) {
    geopackage::WKBWriter writer{geopackage::wkb::Type::EWKB, geopackage::Endian::BIG};
    geopackage::LinearRing ring {{{0,0}, {0, 10}, {10,10}, {10, 0}, {0,0}}};
    geopackage::Polygon polygon {{ring}};
    polygon.setSrid("4326");
    std::string wkbHexString = writer.writeToHex(&polygon);
    geopackage::WKBReader reader{};
    geopackage::Bytes bytes = geopackage::Bytes::fromHexString(geopackage::Endian::BIG, wkbHexString);
    std::unique_ptr<geopackage::Geometry> geometry = reader.read(bytes.getBytes());
    EXPECT_EQ("POLYGON ((0 0, 0 10, 10 10, 10 0, 0 0))", geometry->wkt());
    EXPECT_EQ("4326", geometry->getSrid());
}

TEST(GeoPackageLibTests, WKBReader_MultiPoint_XY_SRID) {
    geopackage::WKBWriter writer{geopackage::wkb::Type::EWKB, geopackage::Endian::BIG};
    geopackage::MultiPoint pts {{{4,5},{1,2},{6,7}}};
    pts.setSrid("4326");
    std::string wkbHexString = writer.writeToHex(&pts);
    geopackage::WKBReader reader{};
    geopackage::Bytes bytes = geopackage::Bytes::fromHexString(geopackage::Endian::BIG, wkbHexString);
    std::unique_ptr<geopackage::Geometry> geometry = reader.read(bytes.getBytes());
    EXPECT_EQ("MULTIPOINT (4 5, 1 2, 6 7)", geometry->wkt());
    EXPECT_EQ("4326", geometry->getSrid());
}

TEST(GeoPackageLibTests, WKBReader_MultiLineString_XY_SRID) {
    geopackage::WKBWriter writer{geopackage::wkb::Type::EWKB, geopackage::Endian::BIG};
    geopackage::MultiLineString multiLine {{ 
        geopackage::LineString {{geopackage::Point {1,1}, geopackage::Point {5,5}}},
        geopackage::LineString {{geopackage::Point {2,2}, geopackage::Point {8,8}}}
    }};
    multiLine.setSrid("4326");
    std::string wkbHexString = writer.writeToHex(&multiLine);
    geopackage::WKBReader reader{};
    geopackage::Bytes bytes = geopackage::Bytes::fromHexString(geopackage::Endian::BIG, wkbHexString);
    std::unique_ptr<geopackage::Geometry> geometry = reader.read(bytes.getBytes());
    EXPECT_EQ("MULTILINESTRING ((1 1, 5 5), (2 2, 8 8))", geometry->wkt());
    EXPECT_EQ("4326", geometry->getSrid());
}

TEST(GeoPackageLibTests, WKBReader_MultiPolygon_XY_SRID) {
    geopackage::WKBWriter writer{geopackage::wkb::Type::EWKB, geopackage::Endian::BIG};
    geopackage::MultiPolygon multiPolygon {{ 
        geopackage::Polygon {{geopackage::LinearRing {{{0,0}, {0, 10}, {10,10}, {10, 0}, {0,0}}} }},
        geopackage::Polygon {{geopackage::LinearRing {{{20,20}, {20, 30}, {30,30}, {30, 20}, {20,20}}} }}
    }};
    multiPolygon.setSrid("4326");
    std::string wkbHexString = writer.writeToHex(&multiPolygon);
    geopackage::WKBReader reader{};
    geopackage::Bytes bytes = geopackage::Bytes::fromHexString(geopackage::Endian::BIG, wkbHexString);
    std::unique_ptr<geopackage::Geometry> geometry = reader.read(bytes.getBytes());
    EXPECT_EQ("MULTIPOLYGON (((0 0, 0 10, 10 10, 10 0, 0 0)), ((20 20, 20 30, 30 30, 30 20, 20 20)))", geometry->wkt());
    EXPECT_EQ("4326", geometry->getSrid());
}

TEST(GeoPackageLibTests, WKBReader_GeometryCollection_XY_SRID) {
    geopackage::WKBWriter writer{geopackage::wkb::Type::EWKB, geopackage::Endian::BIG};
    std::vector<std::unique_ptr<geopackage::Geometry>> geoms;
    geoms.push_back(geopackage::Point {4,5}.clone());
    geoms.push_back(geopackage::LineString {{geopackage::Point{1,1}, geopackage::Point{5,5}}}.clone());
    geopackage::GeometryCollection gc {std::move(geoms)};
    gc.setSrid("4326");
    std::string wkbHexString = writer.writeToHex(&gc);
    geopackage::WKBReader reader{};
    geopackage::Bytes bytes = geopackage::Bytes::fromHexString(geopackage::Endian::BIG, wkbHexString);
    std::unique_ptr<geopackage::Geometry> geometry = reader.read(bytes.getBytes());
    EXPECT_EQ("GEOMETRYCOLLECTION (POINT (4 5), LINESTRING (1 1, 5 5))", geometry->wkt());
    EXPECT_EQ("4326", geometry->getSrid());
}