#include "Geometry.hpp"
#include "MultiLineString.hpp"
#include "gtest/gtest.h"
#include <sstream>

TEST(MultiLineStringTests, multiline_create_test) {
  geopackage::MultiLineString multiLine {{ 
    geopackage::LineString {{geopackage::Point {1,1}, geopackage::Point {5,5}}},
    geopackage::LineString {{geopackage::Point {2,2}, geopackage::Point {8,8}}}
  }};
  ASSERT_EQ(2, std::size(multiLine.getLineStrings()));
  ASSERT_EQ("LINESTRING (1 1, 5 5)", multiLine.getLineStrings()[0].wkt());
  ASSERT_EQ("LINESTRING (2 2, 8 8)", multiLine.getLineStrings()[1].wkt());
}

TEST(MultiLineStringTests, multiline_wkt_test) {
  geopackage::MultiLineString multiLine {{ 
    geopackage::LineString {{geopackage::Point {1,1}, geopackage::Point {5,5}}},
    geopackage::LineString {{geopackage::Point {2,2}, geopackage::Point {8,8}}}
  }};
  ASSERT_EQ("MULTILINESTRING ((1 1, 5 5), (2 2, 8 8))", multiLine.wkt());
}

TEST(MultiLineStringTests, multiline_clone_test) {
  geopackage::MultiLineString multiLine {{ 
    geopackage::LineString {{geopackage::Point {1,1}, geopackage::Point {5,5}}},
    geopackage::LineString {{geopackage::Point {2,2}, geopackage::Point {8,8}}}
  }};
  std::unique_ptr<geopackage::Geometry> clonedGeometry = multiLine.clone();
  geopackage::MultiLineString clonedMultiLineString = static_cast<geopackage::MultiLineString&>(*clonedGeometry);
  ASSERT_EQ(2, std::size(clonedMultiLineString.getLineStrings()));
  ASSERT_EQ("LINESTRING (1 1, 5 5)", clonedMultiLineString.getLineStrings()[0].wkt());
  ASSERT_EQ("LINESTRING (2 2, 8 8)", clonedMultiLineString.getLineStrings()[1].wkt());
}

TEST(MultiLineStringTests, multiline_tostring_test) {
  std::stringstream str;
  geopackage::MultiLineString multiLine {{ 
    geopackage::LineString {{geopackage::Point {1,1}, geopackage::Point {5,5}}},
    geopackage::LineString {{geopackage::Point {2,2}, geopackage::Point {8,8}}}
  }};
  str << multiLine;
  ASSERT_EQ("MULTILINESTRING ((1 1, 5 5), (2 2, 8 8))", str.str());
}