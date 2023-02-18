#include "Schema.hpp"
#include "gtest/gtest.h"
#include <sstream>

TEST(GeoPackageLibTests, schema_create_test) {
  geopackage::Schema schema { "points", geopackage::GeometryField{"geom", geopackage::GeometryType::POINT}, std::vector<geopackage::Field> { 
      geopackage::Field {"id", geopackage::FieldType::Integer}, 
      geopackage::Field {"name", geopackage::FieldType::String}
  }};
  ASSERT_EQ(geopackage::GeometryType::POINT, schema.getGeometryField().getType());
  ASSERT_EQ(2, std::size(schema.getFields()));
  ASSERT_EQ("id", schema.getFields()[0].getName());
  ASSERT_EQ("name", schema.getFields()[1].getName());
  ASSERT_EQ(geopackage::FieldType::Integer, schema.getFields()[0].getType());
  ASSERT_EQ(geopackage::FieldType::String, schema.getFields()[1].getType());
}