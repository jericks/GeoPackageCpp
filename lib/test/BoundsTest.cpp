#include "Bounds.hpp"
#include "gtest/gtest.h"
#include <sstream>

TEST(GeoPackageLibTests, bounds_create_test) {
  geopackage::Bounds b {-180,-90,180,90};
  ASSERT_EQ(-180, b.getMinX());
  ASSERT_EQ(-90, b.getMinY());
  ASSERT_EQ(180, b.getMaxX());
  ASSERT_EQ(90, b.getMaxY());
}

TEST(GeoPackageLibTests, bounds_tostring_test) {
  std::stringstream str;
  geopackage::Bounds b {-180,-90,180,90};
  str << b;
  ASSERT_EQ("BOUNDS (-180, -180, 180, 90)", str.str());
}

TEST(GeoPackageLibTests, bounds_to_polygon_test) {
  std::stringstream str;
  geopackage::Bounds b {-180,-90,180,90};
  std::unique_ptr<geopackage::Polygon> p = b.toPolygon();
  str << p->wkt();
  ASSERT_EQ("POLYGON ((-180 -90, 180 -90, 180 90, -180 -90))", str.str());
}