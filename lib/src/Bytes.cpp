#include "Bytes.hpp"

namespace geopackage {

    Bytes::Bytes(Endian endian) : endian(endian) {}

    Bytes::Bytes(Endian endian, std::vector<std::byte> bytes) : endian(endian), bytes(bytes) {}

    void Bytes::putByte(std::byte value) {
        bytes.push_back(value);
    }

    void Bytes::putBytes(std::vector<std::byte> value) {
        bytes.insert(std::end(bytes), std::begin(value), std::end(value));
    }
    
    void Bytes::putInt(int32_t value) {
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

    void Bytes::putLong(int64_t value) {
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

    int32_t Bytes::getInt() {
        int value;
        if(endian == Endian::BIG) {
            value = static_cast<int32_t>(
                (static_cast<int32_t>((bytes[position + 0] & std::byte{0xff})) << 24) |
                (static_cast<int32_t>((bytes[position + 1] & std::byte{0xff})) << 16) |
                (static_cast<int32_t>((bytes[position + 2] & std::byte{0xff})) << 8)  |
                (static_cast<int32_t>((bytes[position + 3] & std::byte{0xff})))
            );
        } else {
            value = static_cast<int32_t>(
                (static_cast<int32_t>((bytes[position + 3] & std::byte{0xff})) << 24) |
                (static_cast<int32_t>((bytes[position + 2] & std::byte{0xff})) << 16) |
                (static_cast<int32_t>((bytes[position + 1] & std::byte{0xff})) << 8)  |
                (static_cast<int32_t>((bytes[position + 0] & std::byte{0xff})))
            );
        }
        position = position + 4;
        return value;
    }

    int64_t Bytes::getLong() {
        int64_t value;
        if(endian == Endian::BIG) {
            value = static_cast<int64_t>(bytes[position + 0]) << 56 |
                static_cast<int64_t>(bytes[position + 1] & std::byte{0xff}) << 48 |
                static_cast<int64_t>(bytes[position + 2] & std::byte{0xff}) << 40 |
                static_cast<int64_t>(bytes[position + 3] & std::byte{0xff}) << 32 |
                static_cast<int64_t>(bytes[position + 4] & std::byte{0xff}) << 24 |
                static_cast<int64_t>(bytes[position + 5] & std::byte{0xff}) << 16 |
                static_cast<int64_t>(bytes[position + 6] & std::byte{0xff}) <<  8 |
                static_cast<int64_t>(bytes[position + 7] & std::byte{0xff});
        } else {
            value = static_cast<int64_t>(bytes[position + 7]) << 56 |
                static_cast<int64_t>(bytes[position + 6] & std::byte{0xff}) << 48 |
                static_cast<int64_t>(bytes[position + 5] & std::byte{0xff}) << 40 |
                static_cast<int64_t>(bytes[position + 4] & std::byte{0xff}) << 32 |
                static_cast<int64_t>(bytes[position + 3] & std::byte{0xff}) << 24 |
                static_cast<int64_t>(bytes[position + 2] & std::byte{0xff}) << 16 |
                static_cast<int64_t>(bytes[position + 1] & std::byte{0xff}) <<  8 |
                static_cast<int64_t>(bytes[position + 0] & std::byte{0xff});
        }
        position = position + 8;
        return value;
    }

    double Bytes::getDouble() {
        int64_t longValue = getLong();
        double doubleValue;
        std::memcpy(&doubleValue, &longValue, sizeof(double));
        return doubleValue;
    }

    std::byte Bytes::getByte() {
        std::byte b = bytes[position];
        position = position + 1;
        return b;
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

    Bytes Bytes::fromHexString(Endian endian, std::string hexString) {
        std::vector<std::byte> bytes;
        for (unsigned int i = 0; i < hexString.size(); i += 2) {
            std::string byteString = hexString.substr(i, 2);
            const long l = strtol(byteString.c_str(), NULL, 16);
            char c = static_cast<char>(l);
            std::byte byte = static_cast<std::byte>(c);
            bytes.push_back(byte);
        }
        return Bytes{endian, bytes};
    }

    std::ostream& operator << (std::ostream& os, const Bytes& bytes) {
        os << bytes.toHexString();
        return os;
    }

}