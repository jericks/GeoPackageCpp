#include "FieldType.hpp"
#include "gtest/gtest.h"
#include <sstream>

TEST(GeoPackageLibTests, field_type_string_to_string_test) {
  std::stringstream str;
  geopackage::FieldType type = geopackage::FieldType::String;
  str << type;
  ASSERT_EQ("string", str.str());
}

TEST(GeoPackageLibTests, field_type_integer_to_string_test) {
  std::stringstream str;
  geopackage::FieldType type = geopackage::FieldType::Integer;
  str << type;
  ASSERT_EQ("integer", str.str());
}

TEST(GeoPackageLibTests, field_type_double_to_string_test) {
  std::stringstream str;
  geopackage::FieldType type = geopackage::FieldType::Double;
  str << type;
  ASSERT_EQ("double", str.str());
}

TEST(GeoPackageLibTests, field_type_logical_to_string_test) {
  std::stringstream str;
  geopackage::FieldType type = geopackage::FieldType::Boolean;
  str << type;
  ASSERT_EQ("boolean", str.str());
}

TEST(GeoPackageLibTests, field_type_invalid_to_string_test) {
  std::stringstream str;
  geopackage::FieldType type = geopackage::FieldType::Boolean;
  str << type;
  ASSERT_EQ("boolean", str.str());
}