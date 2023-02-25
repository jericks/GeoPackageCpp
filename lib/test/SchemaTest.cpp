#include "Schema.hpp"
#include "gtest/gtest.h"
#include <sstream>

TEST(GeoPackageLibTests, schema_create_test) {
  geopackage::Schema schema { "points", "id", geopackage::GeometryField{"geom", geopackage::GeometryType::POINT, 4326}, std::vector<geopackage::Field> { 
      geopackage::Field {"name", geopackage::FieldType::String},
      geopackage::Field {"value", geopackage::FieldType::Double}, 
  }};
  ASSERT_EQ(geopackage::GeometryType::POINT, schema.getGeometryField().getType());
  ASSERT_EQ(2, std::size(schema.getFields()));
  ASSERT_EQ("name", schema.getFields()[0].getName());
  ASSERT_EQ("value", schema.getFields()[1].getName());
  ASSERT_EQ(geopackage::FieldType::String, schema.getFields()[0].getType());
  ASSERT_EQ(geopackage::FieldType::Double, schema.getFields()[1].getType());
}