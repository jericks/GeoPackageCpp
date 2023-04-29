#include "Geometry.hpp"
#include "Polygon.hpp"
#include "gtest/gtest.h"
#include <sstream>

TEST(PolygonTests, polygon_create_test) {
  geopackage::LinearRing ring {{{0,0}, {0, 10}, {10,10}, {10, 0}, {0,0}}};
  geopackage::Polygon polygon {{ring}};
  ASSERT_EQ(1, std::size(polygon.getLinearRings()));
  ASSERT_EQ(5, std::size(polygon.getLinearRings()[0].getPoints()));
  ASSERT_EQ(0, polygon.getLinearRings()[0].getPoints()[0].getX());
  ASSERT_EQ(0, polygon.getLinearRings()[0].getPoints()[0].getY());
  ASSERT_EQ(0, polygon.getLinearRings()[0].getPoints()[1].getX());
  ASSERT_EQ(10, polygon.getLinearRings()[0].getPoints()[1].getY());
  ASSERT_EQ(0, polygon.getLinearRings()[0].getPoints()[4].getX());
  ASSERT_EQ(0, polygon.getLinearRings()[0].getPoints()[4].getY());
}

TEST(PolygonTests, polygon_wkt_test) {
  geopackage::LinearRing ring {{{0,0}, {0, 10}, {10,10}, {10, 0}, {0,0}}};
  geopackage::Polygon polygon {{ring}};
  ASSERT_EQ("POLYGON ((0 0, 0 10, 10 10, 10 0, 0 0))", polygon.wkt());
}

TEST(PolygonTests, polygon_clone_test) {
  geopackage::LinearRing ring {{{0,0}, {0, 10}, {10,10}, {10, 0}, {0,0}}};
  geopackage::Polygon polygon {{ring}};
  std::unique_ptr<geopackage::Geometry> clonedGeometry = polygon.clone();
  geopackage::Polygon clonedPolygon = static_cast<geopackage::Polygon&>(*clonedGeometry);
  ASSERT_EQ(1, std::size(clonedPolygon.getLinearRings()));
  ASSERT_EQ(5, std::size(clonedPolygon.getLinearRings()[0].getPoints()));
  ASSERT_EQ(0, clonedPolygon.getLinearRings()[0].getPoints()[0].getX());
  ASSERT_EQ(0, clonedPolygon.getLinearRings()[0].getPoints()[0].getY());
  ASSERT_EQ(0, clonedPolygon.getLinearRings()[0].getPoints()[1].getX());
  ASSERT_EQ(10, clonedPolygon.getLinearRings()[0].getPoints()[1].getY());
  ASSERT_EQ(0, clonedPolygon.getLinearRings()[0].getPoints()[4].getX());
  ASSERT_EQ(0, clonedPolygon.getLinearRings()[0].getPoints()[4].getY());
}

TEST(PolygonTests, polygon_tostring_test) {
  std::stringstream str;
  geopackage::LinearRing ring {{{0,0}, {0, 10}, {10,10}, {10, 0}, {0,0}}};
  geopackage::Polygon polygon {{ring}};
  str << polygon;
  ASSERT_EQ("POLYGON ((0 0, 0 10, 10 10, 10 0, 0 0))", str.str());
}