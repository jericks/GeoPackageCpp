#include "Geometry.hpp"
#include "Point.hpp"
#include "gtest/gtest.h"
#include <sstream>

TEST(PointTests, point_create_test) {
  geopackage::Point pt {4,5};
  ASSERT_EQ(4, pt.getX());
  ASSERT_EQ(5, pt.getY());
}

TEST(PointTests, point_srid_test) {
  geopackage::Point pt {4,5};
  pt.setSrid("4326");
  ASSERT_EQ(4, pt.getX());
  ASSERT_EQ(5, pt.getY());
  ASSERT_EQ("4326", pt.getSrid());
}

TEST(PointTests, point_empty_test) {
  geopackage::Point pt = geopackage::Point::empty();
  ASSERT_TRUE(isnan(pt.getX()));
  ASSERT_TRUE(isnan(pt.getX()));
  ASSERT_EQ("POINT EMPTY", pt.wkt());
}

TEST(PointTests, point_wkt_test) {
  geopackage::Point pt {4,5};
  ASSERT_EQ("POINT (4 5)", pt.wkt());
}

TEST(PointTests, point_clone_test) {
  geopackage::Point pt {4,5};
  std::unique_ptr<geopackage::Geometry> clonedGeometry = pt.clone();
  geopackage::Point clonedPoint = static_cast<geopackage::Point&>(*clonedGeometry);
  ASSERT_EQ(4, clonedPoint.getX());
  ASSERT_EQ(5, clonedPoint.getY());
}

TEST(PointTests, point_tostring_test) {
  std::stringstream str;
  geopackage::Point pt {4,5};
  str << pt;
  ASSERT_EQ("POINT (4 5)", str.str());
}

TEST(PointTests, point_create_xy_test) {
  std::stringstream str;
  geopackage::Point pt = geopackage::Point::xy(1.23, 3.45);
  str << pt;
  ASSERT_EQ("POINT (1.23 3.45)", str.str());
  ASSERT_EQ(geopackage::Dimension::Two, pt.getDimension());
}

TEST(PointTests, point_create_xyz_test) {
  std::stringstream str;
  geopackage::Point pt = geopackage::Point::xyz(1.23, 3.45, 10.89);
  str << pt;
  ASSERT_EQ("POINT Z (1.23 3.45 10.89)", str.str());
  ASSERT_EQ(geopackage::Dimension::Three, pt.getDimension());
}

TEST(PointTests, point_create_xym_test) {
  std::stringstream str;
  geopackage::Point pt = geopackage::Point::xym(1.23, 3.45, 10.89);
  str << pt;
  ASSERT_EQ("POINT M (1.23 3.45 10.89)", str.str());
  ASSERT_EQ(geopackage::Dimension::TwoMeasured, pt.getDimension());
}

TEST(PointTests, point_create_xyzm_test) {
  std::stringstream str;
  geopackage::Point pt = geopackage::Point::xyzm(1.23, 3.45, 10.89, 22.32);
  str << pt;
  ASSERT_EQ("POINT ZM (1.23 3.45 10.89 22.32)", str.str());
  ASSERT_EQ(geopackage::Dimension::ThreeMeasured, pt.getDimension());
}