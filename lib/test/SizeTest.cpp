#include "Size.hpp"
#include "gtest/gtest.h"
#include <sstream>


TEST(SizeTest, IntCreate) {
    geopackage::Size<int> intSize {10,12};
    EXPECT_EQ(10, intSize.getWidth());
    EXPECT_EQ(12, intSize.getHeight());
    std::stringstream str;
    str << intSize;
    EXPECT_EQ("SIZE (10, 12)", str.str());
}

TEST(SizeTest, DoubleCreate) {
    geopackage::Size<double> size {1.2,3.4};
    EXPECT_EQ(1.2, size.getWidth());
    EXPECT_EQ(3.4, size.getHeight());
    std::stringstream str;
    str << size;
    EXPECT_EQ("SIZE (1.2, 3.4)", str.str());
}

TEST(SizeTest, FromString) {
  geopackage::Size<int> size = geopackage::size::fromIntString("1,2");
  ASSERT_EQ(1, size.getWidth());
  ASSERT_EQ(2, size.getHeight());
}
