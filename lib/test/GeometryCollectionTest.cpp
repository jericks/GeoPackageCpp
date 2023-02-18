#include "GeometryCollection.hpp"
#include "Point.hpp"
#include "LineString.hpp"
#include "gtest/gtest.h"
#include <sstream>

TEST(GeoPackageLibTests, GeometryCollection_Create_Test) {
   std::vector<std::unique_ptr<geopackage::Geometry>> geoms;
   geoms.push_back(geopackage::Point {4,5}.clone());
   geoms.push_back(geopackage::LineString {{geopackage::Point{1,1}, geopackage::Point{5,5}}}.clone());
   geopackage::GeometryCollection gc {std::move(geoms)};
   ASSERT_EQ(2, gc.getGeometries().size());
   ASSERT_EQ("GEOMETRYCOLLECTION (POINT (4 5), LINESTRING (1 1, 5 5))", gc.wkt()); 
}