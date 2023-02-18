#include "Geometry.hpp"
#include "Point.hpp"
#include "LineString.hpp"
#include "gtest/gtest.h"
#include <sstream>

TEST(GeoPackageLibTests, line_create_test) {
  geopackage::Point pt1 {1,1};
  geopackage::Point pt2 {5,5};
  geopackage::LineString line {{pt1, pt2}};
  ASSERT_EQ(2, std::size(line.getPoints()));
  ASSERT_EQ(1, line.getPoints()[0].getX());
  ASSERT_EQ(1, line.getPoints()[0].getY());
  ASSERT_EQ(5, line.getPoints()[1].getX());
  ASSERT_EQ(5, line.getPoints()[1].getY());
}

TEST(GeoPackageLibTests, line_wkt_test) {
  geopackage::LineString line {{geopackage::Point {1,1}, geopackage::Point {5,5}}};
  ASSERT_EQ("LINESTRING (1 1, 5 5)", line.wkt());
}

TEST(GeoPackageLibTests, line_clone_test) {
  geopackage::Point pt1 {1,1};
  geopackage::Point pt2 {5,5};
  geopackage::LineString line {{pt1, pt2}};
  std::unique_ptr<geopackage::Geometry> clonedGeometry = line.clone();
  geopackage::LineString clonedLineString = static_cast<geopackage::LineString&>(*clonedGeometry);
  ASSERT_EQ(2, std::size(clonedLineString.getPoints()));
  ASSERT_EQ(1, clonedLineString.getPoints()[0].getX());
  ASSERT_EQ(1, clonedLineString.getPoints()[0].getY());
  ASSERT_EQ(5, clonedLineString.getPoints()[1].getX());
  ASSERT_EQ(5, clonedLineString.getPoints()[1].getY());
}

TEST(GeoPackageLibTests, line_tostring_test) {
  std::stringstream str;
  geopackage::LineString line {{geopackage::Point {1,1}, geopackage::Point {5,5}}};
  str << line;
  ASSERT_EQ("LINESTRING (1 1, 5 5)", str.str());
}