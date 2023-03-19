#include <sstream>
#include "gtest/gtest.h"
#include "BinaryType.hpp"

TEST(BinaryTypeTests,  toString) {
    EXPECT_EQ("Standard", geopackage::binarytype::toString(geopackage::BinaryType::Standard));
    EXPECT_EQ("Extended", geopackage::binarytype::toString(geopackage::BinaryType::Extended));
}

TEST(BinaryTypeTests,  getValue) {
    EXPECT_EQ(0, geopackage::binarytype::getValue(geopackage::BinaryType::Standard));
    EXPECT_EQ(1, geopackage::binarytype::getValue(geopackage::BinaryType::Extended));
}

TEST(BinaryTypeTests,  getByte) {
    EXPECT_EQ(std::to_integer<int>(std::byte{0}), std::to_integer<int>(geopackage::binarytype::getByte(geopackage::BinaryType::Standard)));
    EXPECT_EQ(std::to_integer<int>(std::byte{1}), std::to_integer<int>(geopackage::binarytype::getByte(geopackage::BinaryType::Extended)));
}

TEST(BinaryTypeTests,  Print) {
    std::stringstream str1;
    str1 << geopackage::BinaryType::Standard;
    EXPECT_EQ("Standard", str1.str());
    
    std::stringstream str2;
    str2 << geopackage::BinaryType::Extended;
    EXPECT_EQ("Extended", str2.str());
}

