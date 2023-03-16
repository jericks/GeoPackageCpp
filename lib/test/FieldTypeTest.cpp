#include "FieldType.hpp"
#include "gtest/gtest.h"
#include <sstream>

TEST(GeoPackageLibTests, field_type_string_to_string_test) {
  std::stringstream str;
  geopackage::FieldType type = geopackage::FieldType::String;
  str << type;
  ASSERT_EQ("String", str.str());
}

TEST(GeoPackageLibTests, field_type_integer_to_string_test) {
  std::stringstream str;
  geopackage::FieldType type = geopackage::FieldType::Integer;
  str << type;
  ASSERT_EQ("Integer", str.str());
}

TEST(GeoPackageLibTests, field_type_double_to_string_test) {
  std::stringstream str;
  geopackage::FieldType type = geopackage::FieldType::Double;
  str << type;
  ASSERT_EQ("Double", str.str());
}

TEST(GeoPackageLibTests, field_type_logical_to_string_test) {
  std::stringstream str;
  geopackage::FieldType type = geopackage::FieldType::Boolean;
  str << type;
  ASSERT_EQ("Boolean", str.str());
}

TEST(GeoPackageLibTests, field_type_invalid_to_string_test) {
  std::stringstream str;
  geopackage::FieldType type = geopackage::FieldType::Boolean;
  str << type;
  ASSERT_EQ("Boolean", str.str());
}