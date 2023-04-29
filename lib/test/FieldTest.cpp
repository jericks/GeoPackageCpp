#include "Field.hpp"
#include "gtest/gtest.h"
#include <sstream>

TEST(FieldTests, field_create_test) {
  geopackage::Field field {"id", geopackage::FieldType::Integer};
  ASSERT_EQ("id", field.getName());
  ASSERT_EQ(geopackage::FieldType::Integer, field.getType());
}

TEST(FieldTests, field_tostring_test) {
  std::stringstream str;
  geopackage::Field field {"id", geopackage::FieldType::Integer};
  str << field;
  ASSERT_EQ("Field(name=id, type=Integer)", str.str());
}

TEST(FieldTests, field_create_string_test) {
  std::stringstream str;
  geopackage::Field field = geopackage::Field::createStringField("type");
  str << field;
  ASSERT_EQ("Field(name=type, type=String)", str.str());
}

TEST(FieldTests, field_create_integer_test) {
  std::stringstream str;
  geopackage::Field field = geopackage::Field::createIntegerField("id");
  str << field;
  ASSERT_EQ("Field(name=id, type=Integer)", str.str());
}

TEST(FieldTests, field_create_double_test) {
  std::stringstream str;
  geopackage::Field field = geopackage::Field::createDoubleField("value");
  str << field;
  ASSERT_EQ("Field(name=value, type=Double)", str.str());
}

TEST(FieldTests, field_create_logical_test) {
  std::stringstream str;
  geopackage::Field field = geopackage::Field::createBooleanField("active");
  str << field;
  ASSERT_EQ("Field(name=active, type=Boolean)", str.str());
}