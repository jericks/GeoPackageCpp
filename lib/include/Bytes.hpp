#pragma once

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
        
        public:

            Bytes(Endian endian);

            void putByte(std::byte value);

            void putBytes(std::vector<std::byte> value);
            
            void putInt(int value);

            void putLong(long value);

            void putDouble(double value);

            std::vector<std::byte> getBytes() const;

            std::string toHexString() const;

    };

    std::ostream& operator << (std::ostream& os, const Bytes& bytes);

}