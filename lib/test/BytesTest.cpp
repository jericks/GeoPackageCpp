#include "Bytes.hpp"
#include "gtest/gtest.h"
#include <sstream>

TEST(BytesTests, Bytes_toHexString) {
  geopackage::Bytes bytes{geopackage::Endian::BIG};
  bytes.putInt(1);
  bytes.putInt(2);
  bytes.putInt(3);
  ASSERT_EQ("000000010000000200000003", bytes.toHexString());
}

TEST(BytesTests, Bytes_fromHexString) {
  geopackage::Bytes bytes = geopackage::Bytes::fromHexString(geopackage::Endian::BIG, "000000010000000200000003");
  ASSERT_EQ(1, bytes.getInt());
  ASSERT_EQ(2, bytes.getInt());
  ASSERT_EQ(3, bytes.getInt());
  ASSERT_EQ("000000010000000200000003", bytes.toHexString());
}

TEST(BytesTests, Bytes_GetPutByte_Big) {
  geopackage::Bytes bytes{geopackage::Endian::BIG};
  bytes.putByte(std::byte{1});
  bytes.putByte(std::byte{2});
  bytes.putByte(std::byte{3});
  ASSERT_EQ(std::byte{1}, bytes.getByte());
  ASSERT_EQ(std::byte{2}, bytes.getByte());
  ASSERT_EQ(std::byte{3}, bytes.getByte());
}

TEST(BytesTests, Bytes_GetPutByte_Little) {
  geopackage::Bytes bytes{geopackage::Endian::LITTLE};
  bytes.putByte(std::byte{1});
  bytes.putByte(std::byte{2});
  bytes.putByte(std::byte{3});
  ASSERT_EQ(std::byte{1}, bytes.getByte());
  ASSERT_EQ(std::byte{2}, bytes.getByte());
  ASSERT_EQ(std::byte{3}, bytes.getByte());
}

TEST(BytesTests, Bytes_GetPutInt_Big) {
  geopackage::Bytes bytes{geopackage::Endian::BIG};
  bytes.putInt(11);
  bytes.putInt(22);
  bytes.putInt(33);
  ASSERT_EQ(11, bytes.getInt());
  ASSERT_EQ(22, bytes.getInt());
  ASSERT_EQ(33, bytes.getInt());
}

TEST(BytesTests, Bytes_GetPutInt_Little) {
  geopackage::Bytes bytes{geopackage::Endian::LITTLE};
  bytes.putInt(11);
  bytes.putInt(22);
  bytes.putInt(33);
  ASSERT_EQ(11, bytes.getInt());
  ASSERT_EQ(22, bytes.getInt());
  ASSERT_EQ(33, bytes.getInt());
}

TEST(BytesTests, Bytes_GetPutLong_Big) {
  geopackage::Bytes bytes{geopackage::Endian::BIG};
  bytes.putLong(123);
  bytes.putLong(290);
  bytes.putLong(789);
  ASSERT_EQ(123, bytes.getLong());
  ASSERT_EQ(290, bytes.getLong());
  ASSERT_EQ(789, bytes.getLong());
}

TEST(BytesTests, Bytes_GetPutLong_Little) {
  geopackage::Bytes bytes{geopackage::Endian::LITTLE};
  bytes.putLong(123);
  bytes.putLong(290);
  bytes.putLong(789);
  ASSERT_EQ(123, bytes.getLong());
  ASSERT_EQ(290, bytes.getLong());
  ASSERT_EQ(789, bytes.getLong());
}

TEST(BytesTests, Bytes_GetPutDouble_Big) {
  geopackage::Bytes bytes{geopackage::Endian::BIG};
  bytes.putDouble(123.1);
  bytes.putDouble(456.2);
  bytes.putDouble(789.3);
  bytes.putDouble(-122.3894562);
  bytes.putDouble(-122.3894562);
  ASSERT_EQ(123.1, bytes.getDouble());
  ASSERT_EQ(456.2, bytes.getDouble());
  ASSERT_EQ(789.3, bytes.getDouble());
  ASSERT_EQ(-122.3894562, bytes.getDouble());
  ASSERT_EQ(-122.3894562, bytes.getDouble());
}

TEST(BytesTests, Bytes_GetPutDouble_Little) {
  geopackage::Bytes bytes{geopackage::Endian::LITTLE};
  bytes.putDouble(123.1);
  bytes.putDouble(456.2);
  bytes.putDouble(789.3);
  bytes.putDouble(-122.3894562);
  bytes.putDouble(-122.3894562);
  ASSERT_EQ(123.1, bytes.getDouble());
  ASSERT_EQ(456.2, bytes.getDouble());
  ASSERT_EQ(789.3, bytes.getDouble());
  ASSERT_EQ(-122.3894562, bytes.getDouble());
  ASSERT_EQ(-122.3894562, bytes.getDouble());
}