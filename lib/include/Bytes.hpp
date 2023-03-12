#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <ostream>
#include <iomanip>
#include "Endian.hpp"

namespace geopackage {

    class Bytes {

        private:

            Endian endian;

            std::vector<std::byte> bytes;

            int position = 0;
        
        public:

            Bytes(Endian endian);

            Bytes(Endian endian, std::vector<std::byte> bytes);

            void setPosition(int position);

            void putByte(std::byte value);

            void putBytes(std::vector<std::byte> value);
            
            void putInt(int32_t value);

            void putLong(int64_t value);

            void putDouble(double value);

            int32_t getInt();

            int64_t getLong();

            double getDouble();

            std::byte getByte();

            std::vector<std::byte> getBytes() const;

            std::string toHexString() const;

            static Bytes fromHexString(Endian endian, std::string hexString);

    };

    std::ostream& operator << (std::ostream& os, const Bytes& bytes);

}