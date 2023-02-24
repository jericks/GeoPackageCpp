#include "Bytes.hpp"

namespace geopackage {

    Bytes::Bytes(Endian endian) : endian(endian) {}

    void Bytes::putByte(std::byte value) {
        bytes.push_back(value);
    }

    void Bytes::putBytes(std::vector<std::byte> value) {
        bytes.insert(std::end(bytes), std::begin(value), std::end(value));
    }
    
    void Bytes::putInt(int value) {
         if(endian == Endian::BIG) {
            bytes.push_back(static_cast<std::byte>(value >> 24));
            bytes.push_back(static_cast<std::byte>(value >> 16));
            bytes.push_back(static_cast<std::byte>(value >> 8));
            bytes.push_back(static_cast<std::byte>(value));
        } else { 
            bytes.push_back(static_cast<std::byte>(value));
            bytes.push_back(static_cast<std::byte>(value >> 8));
            bytes.push_back(static_cast<std::byte>(value >> 16));
            bytes.push_back(static_cast<std::byte>(value >> 24));
        }
    }

    void Bytes::putLong(long value) {
        if(endian == Endian::BIG) {
            bytes.push_back(static_cast<std::byte>(value >> 56));
            bytes.push_back(static_cast<std::byte>(value >> 48));
            bytes.push_back(static_cast<std::byte>(value >> 40));
            bytes.push_back(static_cast<std::byte>(value >> 32));
            bytes.push_back(static_cast<std::byte>(value >> 24));
            bytes.push_back(static_cast<std::byte>(value >> 16));
            bytes.push_back(static_cast<std::byte>(value >> 8));
            bytes.push_back(static_cast<std::byte>(value));
        } else { 
            bytes.push_back(static_cast<std::byte>(value));
            bytes.push_back(static_cast<std::byte>(value >> 8));
            bytes.push_back(static_cast<std::byte>(value >> 16));
            bytes.push_back(static_cast<std::byte>(value >> 24));
            bytes.push_back(static_cast<std::byte>(value >> 32));
            bytes.push_back(static_cast<std::byte>(value >> 40));
            bytes.push_back(static_cast<std::byte>(value >> 48));
            bytes.push_back(static_cast<std::byte>(value >> 56));
        }
    }

    void Bytes::putDouble(double value) {
        int64_t longValue;
        std::memcpy(&longValue, &value, sizeof(double));
        putLong(longValue);
    }

    std::vector<std::byte> Bytes::getBytes() const {
        return bytes;
    }

    std::string Bytes::toHexString() const {
        std::stringstream ss;
        ss << std::hex << std::uppercase;
        for (int i = 0; i < bytes.size(); ++i) {
            ss << std::setw(2) << std::setfill('0') << (int)bytes[i];
        }
        return ss.str();
    }

    std::ostream& operator << (std::ostream& os, const Bytes& bytes) {
        os << bytes.toHexString();
        return os;
    }

}