#include <sstream>
#include <iostream>
#include <filesystem>
#include <fstream>
#include "gtest/gtest.h"
#include "GeoPackageGeometryReader.hpp"
#include "GeoPackageGeometryWriter.hpp"
#include "Point.hpp"

TEST(GeoPackageLibTests, GeoPackageGeometryReader_Point_XY) {
    geopackage::GeoPackageGeometryWriter writer{};
    geopackage::Point pt {31.19999710971274, -26.466667461352472};
    std::vector<std::byte> bytes = writer.write(&pt);
    geopackage::GeoPackageGeometryReader reader{};
    std::unique_ptr<geopackage::Geometry> geom = reader.read(bytes);
    EXPECT_EQ("POINT (31.2 -26.4667)", geom->wkt());
    EXPECT_EQ("", geom->getSrid());
}

TEST(GeoPackageLibTests, GeoPackageGeometryReader_Point_Srid) {
    geopackage::GeoPackageGeometryWriter writer{};
    geopackage::Point pt {31.19999710971274, -26.466667461352472};
    pt.setSrid("4326");
    std::vector<std::byte> bytes = writer.write(&pt);
    geopackage::GeoPackageGeometryReader reader{};
    std::unique_ptr<geopackage::Geometry> geom = reader.read(bytes);
    EXPECT_EQ("POINT (31.2 -26.4667)", geom->wkt());
    EXPECT_EQ("4326", geom->getSrid());
}

TEST(GeoPackageLibTests, GeoPackageGeometryReader_Point_XYZM) {
    geopackage::GeoPackageGeometryWriter writer{};
    geopackage::Point pt {31.19999710971274, -26.466667461352472, 12.456, 102.391};
    std::vector<std::byte> bytes = writer.write(&pt);
    geopackage::GeoPackageGeometryReader reader{};
    std::unique_ptr<geopackage::Geometry> geom = reader.read(bytes);
    EXPECT_EQ("POINT ZM (31.2 -26.4667 12.456 102.391)", geom->wkt());
    EXPECT_EQ("", geom->getSrid());
}

TEST(GeoPackageLibTests, GeoPackageGeometryReader_LineString) {
    geopackage::GeoPackageGeometryWriter writer{};
    geopackage::LineString line {{geopackage::Point {1,1}, geopackage::Point {5,5}}};
    std::vector<std::byte> bytes = writer.write(&line);
    geopackage::GeoPackageGeometryReader reader{};
    std::unique_ptr<geopackage::Geometry> geom = reader.read(bytes);
    EXPECT_EQ("LINESTRING (1 1, 5 5)", geom->wkt());
    EXPECT_EQ("", geom->getSrid());
}

TEST(GeoPackageLibTests, GeoPackageGeometryReader_Polygon) {
    geopackage::GeoPackageGeometryWriter writer{};
    geopackage::LinearRing ring {{{0,0}, {0, 10}, {10,10}, {10, 0}, {0,0}}};
    geopackage::Polygon polygon {{ring}};
    std::vector<std::byte> bytes = writer.write(&polygon);
    geopackage::GeoPackageGeometryReader reader{};
    std::unique_ptr<geopackage::Geometry> geom = reader.read(bytes);
    EXPECT_EQ("POLYGON ((0 0, 0 10, 10 10, 10 0, 0 0))", geom->wkt());
    EXPECT_EQ("", geom->getSrid());
}

TEST(GeoPackageLibTests, GeoPackageGeometryReader_MultiPoint) {
    geopackage::GeoPackageGeometryWriter writer{};
    geopackage::MultiPoint pts {{{4,5},{1,2},{6,7}}};
    std::vector<std::byte> bytes = writer.write(&pts);
    geopackage::GeoPackageGeometryReader reader{};
    std::unique_ptr<geopackage::Geometry> geom = reader.read(bytes);
    EXPECT_EQ("MULTIPOINT (4 5, 1 2, 6 7)", geom->wkt());
    EXPECT_EQ("", geom->getSrid());
}


TEST(GeoPackageLibTests, GeoPackageGeometryReader_MultiLineString) {
    geopackage::GeoPackageGeometryWriter writer{};
    geopackage::MultiLineString multiLine {{ 
        geopackage::LineString {{geopackage::Point {1,1}, geopackage::Point {5,5}}},
        geopackage::LineString {{geopackage::Point {2,2}, geopackage::Point {8,8}}}
    }};
    std::vector<std::byte> bytes = writer.write(&multiLine);
    geopackage::GeoPackageGeometryReader reader{};
    std::unique_ptr<geopackage::Geometry> geom = reader.read(bytes);
    EXPECT_EQ("MULTILINESTRING ((1 1, 5 5), (2 2, 8 8))", geom->wkt());
    EXPECT_EQ("", geom->getSrid());
}

TEST(GeoPackageLibTests, GeoPackageGeometryReader_MultiPolygon) {
    geopackage::GeoPackageGeometryWriter writer{};
    geopackage::MultiPolygon multiPolygon {{ 
        geopackage::Polygon {{geopackage::LinearRing {{{0,0}, {0, 10}, {10,10}, {10, 0}, {0,0}}} }},
        geopackage::Polygon {{geopackage::LinearRing {{{20,20}, {20, 30}, {30,30}, {30, 20}, {20,20}}} }}
    }};
    std::vector<std::byte> bytes = writer.write(&multiPolygon);
    geopackage::GeoPackageGeometryReader reader{};
    std::unique_ptr<geopackage::Geometry> geom = reader.read(bytes);
    EXPECT_EQ("MULTIPOLYGON (((0 0, 0 10, 10 10, 10 0, 0 0)), ((20 20, 20 30, 30 30, 30 20, 20 20)))", geom->wkt());
    EXPECT_EQ("", geom->getSrid());
}

TEST(GeoPackageLibTests, GeoPackageGeometryReader_GeometryCollection) {
    geopackage::GeoPackageGeometryWriter writer{};
    std::vector<std::unique_ptr<geopackage::Geometry>> geoms;
    geoms.push_back(geopackage::Point {4,5}.clone());
    geoms.push_back(geopackage::LineString {{geopackage::Point{1,1}, geopackage::Point{5,5}}}.clone());
    geopackage::GeometryCollection gc {std::move(geoms)};
    std::vector<std::byte> bytes = writer.write(&gc);
    geopackage::GeoPackageGeometryReader reader{};
    std::unique_ptr<geopackage::Geometry> geom = reader.read(bytes);
    EXPECT_EQ("GEOMETRYCOLLECTION (POINT (4 5), LINESTRING (1 1, 5 5))", geom->wkt());
    EXPECT_EQ("", geom->getSrid());
}