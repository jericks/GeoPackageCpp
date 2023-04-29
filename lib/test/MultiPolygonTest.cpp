#include "MultiPolygon.hpp"
#include "gtest/gtest.h"
#include <sstream>

TEST(MultiPolygonTests, multipolygon_create_test) {
  geopackage::MultiPolygon multiPolygon {{ 
    geopackage::Polygon {{geopackage::LinearRing {{{0,0}, {0, 10}, {10,10}, {10, 0}, {0,0}}} }},
    geopackage::Polygon {{geopackage::LinearRing {{{20,20}, {20, 30}, {30,30}, {30, 20}, {20,20}}} }}
  }};
  ASSERT_EQ(2, std::size(multiPolygon.getPolygons()));
  ASSERT_EQ("POLYGON ((0 0, 0 10, 10 10, 10 0, 0 0))", multiPolygon.getPolygons()[0].wkt());
  ASSERT_EQ("POLYGON ((20 20, 20 30, 30 30, 30 20, 20 20))", multiPolygon.getPolygons()[1].wkt());
}

TEST(MultiPolygonTests, multipolygon_wkt_test) {
  geopackage::MultiPolygon multiPolygon {{ 
    geopackage::Polygon {{geopackage::LinearRing {{{0,0}, {0, 10}, {10,10}, {10, 0}, {0,0}}} }},
    geopackage::Polygon {{geopackage::LinearRing {{{20,20}, {20, 30}, {30,30}, {30, 20}, {20,20}}} }}
  }};
  ASSERT_EQ("MULTIPOLYGON (((0 0, 0 10, 10 10, 10 0, 0 0)), ((20 20, 20 30, 30 30, 30 20, 20 20)))", multiPolygon.wkt());
}

TEST(MultiPolygonTests, multipolygon_clone_test) {
  geopackage::MultiPolygon multiPolygon {{ 
    geopackage::Polygon {{geopackage::LinearRing {{{0,0}, {0, 10}, {10,10}, {10, 0}, {0,0}}} }},
    geopackage::Polygon {{geopackage::LinearRing {{{20,20}, {20, 30}, {30,30}, {30, 20}, {20,20}}} }}
  }};
  std::unique_ptr<geopackage::Geometry> clonedGeometry = multiPolygon.clone();
  geopackage::MultiPolygon clonedMultiPolygon = static_cast<geopackage::MultiPolygon&>(*clonedGeometry);
  ASSERT_EQ(2, std::size(clonedMultiPolygon.getPolygons()));
  ASSERT_EQ("POLYGON ((0 0, 0 10, 10 10, 10 0, 0 0))", clonedMultiPolygon.getPolygons()[0].wkt());
  ASSERT_EQ("POLYGON ((20 20, 20 30, 30 30, 30 20, 20 20))", clonedMultiPolygon.getPolygons()[1].wkt());
}

TEST(MultiPolygonTests, multipolygon_tostring_test) {
  std::stringstream str;
  geopackage::MultiPolygon multiPolygon {{ 
    geopackage::Polygon {{geopackage::LinearRing {{{0,0}, {0, 10}, {10,10}, {10, 0}, {0,0}}} }},
    geopackage::Polygon {{geopackage::LinearRing {{{20,20}, {20, 30}, {30,30}, {30, 20}, {20,20}}} }}
  }};
  str << multiPolygon;
  ASSERT_EQ("MULTIPOLYGON (((0 0, 0 10, 10 10, 10 0, 0 0)), ((20 20, 20 30, 30 30, 30 20, 20 20)))", str.str());
}