#include "Geometry.hpp"
#include "Point.hpp"
#include "LinearRing.hpp"
#include "gtest/gtest.h"
#include <sstream>

TEST(GeoPackageLibTests, linearring_create_test) {
  geopackage::LinearRing ring {{{0,0}, {0, 10}, {10,10}, {10, 0}, {0,0}}};
  ASSERT_EQ(5, std::size(ring.getPoints()));
  ASSERT_EQ(0, ring.getPoints()[0].getX());
  ASSERT_EQ(0, ring.getPoints()[0].getY());
  ASSERT_EQ(0, ring.getPoints()[1].getX());
  ASSERT_EQ(10, ring.getPoints()[1].getY());
  ASSERT_EQ(0, ring.getPoints()[4].getX());
  ASSERT_EQ(0, ring.getPoints()[4].getY());
}

TEST(GeoPackageLibTests, linearring_wkt_test) {
  geopackage::LinearRing ring {{{0,0}, {0, 10}, {10,10}, {10, 0}, {0,0}}};
  ASSERT_EQ("LINEARRING (0 0, 0 10, 10 10, 10 0, 0 0)", ring.wkt());
}

TEST(GeoPackageLibTests, linearring_clone_test) {
  geopackage::LinearRing ring {{{0,0}, {0, 10}, {10,10}, {10, 0}, {0,0}}};
  std::unique_ptr<geopackage::Geometry> clonedGeometry = ring.clone();
  geopackage::LinearRing clonedLinearRing = static_cast<geopackage::LinearRing&>(*clonedGeometry);
  ASSERT_EQ(5, std::size(clonedLinearRing.getPoints()));
  ASSERT_EQ(0, clonedLinearRing.getPoints()[0].getX());
  ASSERT_EQ(0, clonedLinearRing.getPoints()[0].getY());
  ASSERT_EQ(0, clonedLinearRing.getPoints()[1].getX());
  ASSERT_EQ(10, clonedLinearRing.getPoints()[1].getY());
}

TEST(GeoPackageLibTests, linearring_tostlinearring_test) {
  std::stringstream str;
  geopackage::LinearRing ring {{{0,0}, {0, 10}, {10,10}, {10, 0}, {0,0}}};
  str << ring;
  ASSERT_EQ("LINEARRING (0 0, 0 10, 10 10, 10 0, 0 0)", str.str());
}