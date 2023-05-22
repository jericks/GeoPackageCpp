#include "Dimension.hpp"
#include "gtest/gtest.h"
#include <sstream>

TEST(DimensionTests, toString) {
  ASSERT_EQ("2D", geopackage::dimension::toString(geopackage::Dimension::Two));
  ASSERT_EQ("2DM", geopackage::dimension::toString(geopackage::Dimension::TwoMeasured));
  ASSERT_EQ("3D", geopackage::dimension::toString(geopackage::Dimension::Three));
  ASSERT_EQ("3DM", geopackage::dimension::toString(geopackage::Dimension::ThreeMeasured));
}

TEST(DimensionTests, fromString) {
  ASSERT_EQ(geopackage::Dimension::Two, geopackage::dimension::fromString("2D"));
  ASSERT_EQ(geopackage::Dimension::TwoMeasured, geopackage::dimension::fromString("2DM"));
  ASSERT_EQ(geopackage::Dimension::Three, geopackage::dimension::fromString("3D"));
  ASSERT_EQ(geopackage::Dimension::ThreeMeasured, geopackage::dimension::fromString("3DM"));
}

TEST(DimensionTests, getDimension) {
  ASSERT_EQ(geopackage::Dimension::Two, geopackage::dimension::getDimension(false, false));
  ASSERT_EQ(geopackage::Dimension::TwoMeasured, geopackage::dimension::getDimension(false, true));
  ASSERT_EQ(geopackage::Dimension::Three, geopackage::dimension::getDimension(true, false));
  ASSERT_EQ(geopackage::Dimension::ThreeMeasured, geopackage::dimension::getDimension(true, true));
}

TEST(DimensionTests, hasZ) {
    ASSERT_TRUE(geopackage::dimension::hasZ(geopackage::Dimension::Three));
    ASSERT_TRUE(geopackage::dimension::hasZ(geopackage::Dimension::ThreeMeasured));
    ASSERT_FALSE(geopackage::dimension::hasZ(geopackage::Dimension::Two));
    ASSERT_FALSE(geopackage::dimension::hasZ(geopackage::Dimension::TwoMeasured));
}

TEST(DimensionTests, hasM) {
    ASSERT_TRUE(geopackage::dimension::hasM(geopackage::Dimension::TwoMeasured));
    ASSERT_TRUE(geopackage::dimension::hasM(geopackage::Dimension::ThreeMeasured));
    ASSERT_FALSE(geopackage::dimension::hasM(geopackage::Dimension::Two));
    ASSERT_FALSE(geopackage::dimension::hasM(geopackage::Dimension::Three));
}