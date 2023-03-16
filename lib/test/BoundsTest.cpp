#include "Bounds.hpp"
#include "gtest/gtest.h"
#include <sstream>

TEST(GeoPackageLibTests, Bounds_create_zy_test) {
  geopackage::Bounds b {-180,-90,180,90};
  ASSERT_EQ(-180, b.getMinX());
  ASSERT_EQ(-90, b.getMinY());
  ASSERT_TRUE(isnan(b.getMinZ()));
  ASSERT_TRUE(isnan(b.getMinM()));
  ASSERT_EQ(180, b.getMaxX());
  ASSERT_EQ(90, b.getMaxY());
  ASSERT_TRUE(isnan(b.getMaxZ()));
  ASSERT_TRUE(isnan(b.getMaxM()));
}

TEST(GeoPackageLibTests, Bounds_create_xyzm_test) {
  geopackage::Bounds b {-180, -90, 10, 1.2, 180, 90, 12, 3.4};
  ASSERT_EQ(-180, b.getMinX());
  ASSERT_EQ(-90, b.getMinY());
  ASSERT_EQ(10, b.getMinZ());
  ASSERT_EQ(1.2, b.getMinM());
  ASSERT_EQ(180, b.getMaxX());
  ASSERT_EQ(90, b.getMaxY());
  ASSERT_EQ(12, b.getMaxZ());
  ASSERT_EQ(3.4, b.getMaxM());
}

TEST(GeoPackageLibTests, Bounds_create_static_xy_test) {
  geopackage::Bounds b = geopackage::Bounds::xy(-180,-90,180,90);
  ASSERT_EQ(-180, b.getMinX());
  ASSERT_EQ(-90, b.getMinY());
  ASSERT_TRUE(isnan(b.getMinZ()));
  ASSERT_TRUE(isnan(b.getMinM()));
  ASSERT_EQ(180, b.getMaxX());
  ASSERT_EQ(90, b.getMaxY());
  ASSERT_TRUE(isnan(b.getMaxZ()));
  ASSERT_TRUE(isnan(b.getMaxM()));
}

TEST(GeoPackageLibTests, Bounds_create_static_xyz_test) {
  geopackage::Bounds b = geopackage::Bounds::xyz(-180,-90,1,180,90,101);
  ASSERT_EQ(-180, b.getMinX());
  ASSERT_EQ(-90, b.getMinY());
  ASSERT_EQ(1, b.getMinZ());
  ASSERT_TRUE(isnan(b.getMinM()));
  ASSERT_EQ(180, b.getMaxX());
  ASSERT_EQ(90, b.getMaxY());
  ASSERT_EQ(101, b.getMaxZ());
  ASSERT_TRUE(isnan(b.getMaxM()));
}

TEST(GeoPackageLibTests, Bounds_create_static_xym_test) {
  geopackage::Bounds b = geopackage::Bounds::xym(-180,-90,1,180,90,101);
  ASSERT_EQ(-180, b.getMinX());
  ASSERT_EQ(-90, b.getMinY());
  ASSERT_TRUE(isnan(b.getMinZ()));
  ASSERT_EQ(1, b.getMinM());
  ASSERT_EQ(180, b.getMaxX());
  ASSERT_EQ(90, b.getMaxY());
  ASSERT_TRUE(isnan(b.getMaxZ()));
  ASSERT_EQ(101, b.getMaxM());
}

TEST(GeoPackageLibTests, Bounds_create_static_xyzm_test) {
  geopackage::Bounds b = geopackage::Bounds::xyzm(-180, -90, 10, 1.2, 180, 90, 12, 3.4);
  ASSERT_EQ(-180, b.getMinX());
  ASSERT_EQ(-90, b.getMinY());
  ASSERT_EQ(10, b.getMinZ());
  ASSERT_EQ(1.2, b.getMinM());
  ASSERT_EQ(180, b.getMaxX());
  ASSERT_EQ(90, b.getMaxY());
  ASSERT_EQ(12, b.getMaxZ());
  ASSERT_EQ(3.4, b.getMaxM());
}

TEST(GeoPackageLibTests, Bounds_tostring_test) {
  std::stringstream str;
  geopackage::Bounds b {-180,-90,180,90};
  str << b;
  ASSERT_EQ("BOUNDS (-180, -90, 180, 90)", str.str());
}

TEST(GeoPackageLibTests, Bounds_xyzm_tostring_test) {
  std::stringstream str;
  geopackage::Bounds b {-180, -90, 10, 1.2, 180, 90, 12, 3.4};
  str << b;
  ASSERT_EQ("BOUNDS ZM(-180, -90, 10, 1.2, 180, 90, 12, 3.4)", str.str());
}

TEST(GeoPackageLibTests, Bounds_to_polygon_test) {
  std::stringstream str;
  geopackage::Bounds b {-180,-90,180,90};
  std::unique_ptr<geopackage::Polygon> p = b.toPolygon();
  str << p->wkt();
  ASSERT_EQ("POLYGON ((-180 -90, 180 -90, 180 90, -180 -90))", str.str());
}

TEST(GeoPackageLibTests, Bounds_getBounds_Point) {
  geopackage::Point pt {4,5};
  geopackage::Bounds b = geopackage::Bounds::getBounds(&pt);
  std::stringstream str;
  str << b;
  ASSERT_EQ("BOUNDS (4, 5, 4, 5)", str.str());
}

TEST(GeoPackageLibTests, Bounds_getBounds_LineString) {
  geopackage::LineString line {{geopackage::Point {1,2}, geopackage::Point {4,5}}};
  geopackage::Bounds b = geopackage::Bounds::getBounds(&line);
  std::stringstream str;
  str << b;
  ASSERT_EQ("BOUNDS (1, 2, 4, 5)", str.str());
}

TEST(GeoPackageLibTests, Bounds_getBounds_Polygon) {
   geopackage::LinearRing ring {{{0,0}, {0, 10}, {10,10}, {10, 0}, {0,0}}};
  geopackage::Polygon polygon {{ring}};
  geopackage::Bounds b = geopackage::Bounds::getBounds(&polygon);
  std::stringstream str;
  str << b;
  ASSERT_EQ("BOUNDS (0, 0, 10, 10)", str.str());
}

TEST(GeoPackageLibTests, Bounds_getBounds_MulitPoint) {
  geopackage::MultiPoint pts {{{4,5},{1,2},{6,7}}};
  geopackage::Bounds b = geopackage::Bounds::getBounds(&pts);
  std::stringstream str;
  str << b;
  ASSERT_EQ("BOUNDS (1, 2, 6, 7)", str.str());
}

TEST(GeoPackageLibTests, Bounds_getBounds_MulitLineString) {
  geopackage::MultiLineString multiLine {{ 
    geopackage::LineString {{geopackage::Point {1,1}, geopackage::Point {5,5}}},
    geopackage::LineString {{geopackage::Point {2,2}, geopackage::Point {8,8}}}
  }};
  geopackage::Bounds b = geopackage::Bounds::getBounds(&multiLine);
  std::stringstream str;
  str << b;
  ASSERT_EQ("BOUNDS (1, 1, 8, 8)", str.str());
}

TEST(GeoPackageLibTests, Bounds_getBounds_MulitPolygon) {
  geopackage::MultiPolygon multiPolygon {{ 
    geopackage::Polygon {{geopackage::LinearRing {{{0,0}, {0, 10}, {10,10}, {10, 0}, {0,0}}} }},
    geopackage::Polygon {{geopackage::LinearRing {{{20,20}, {20, 30}, {30,30}, {30, 20}, {20,20}}} }}
  }};
  geopackage::Bounds b = geopackage::Bounds::getBounds(&multiPolygon);
  std::stringstream str;
  str << b;
  ASSERT_EQ("BOUNDS (0, 0, 30, 30)", str.str());
}

TEST(GeoPackageLibTests, Bounds_getBounds_GeometryCollection) {
  std::vector<std::unique_ptr<geopackage::Geometry>> geoms;
  geoms.push_back(geopackage::Point {14,15}.clone());
  geoms.push_back(geopackage::LineString {{geopackage::Point{1,1}, geopackage::Point{5,5}}}.clone());
  geopackage::GeometryCollection gc {std::move(geoms)};
  geopackage::Bounds b = geopackage::Bounds::getBounds(&gc);
  std::stringstream str;
  str << b;
  ASSERT_EQ("BOUNDS (1, 1, 14, 15)", str.str());
}