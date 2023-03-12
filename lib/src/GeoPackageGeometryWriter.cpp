#include "GeoPackageGeometryWriter.hpp"

namespace geopackage {

    std::vector<std::byte> GeoPackageGeometryWriter::write(Geometry* geometry) {
        return writeToBytes(geometry).getBytes();
    }

    std::string GeoPackageGeometryWriter::writeToHex(Geometry* geometry) {
        return writeToBytes(geometry).toHexString();
    }

    Bytes GeoPackageGeometryWriter::writeToBytes(Geometry* geometry) {
        Bytes bytes{endian};
        // Magic
        bytes.putByte(std::byte{'G'});
        bytes.putByte(std::byte{'P'});
        // Version
        bytes.putByte(std::byte{0});
        // Flags
        std::byte flagByte {0};
        // Envelope Type
        std::byte envelopeTypeByte = envelopetype::getByte(envelopeType);
        flagByte = flagByte | ((envelopeTypeByte << 1) & flag::getByte(Flag::EnvelopeIndicator));
        // Binary Type
        flagByte |= flagByte | binarytype::getByte(binaryType) & flag::getByte(Flag::BinaryType);
        // Geometry Empty Type
        flagByte = flagByte | (geometry->isEmpty() ? std::byte{0} : std::byte{1}) & flag::getByte(Flag::GeometryEmpty);
        // Endian
        std::byte endianByte = endian == Endian::BIG ? std::byte{0} : std::byte{1};
        flagByte = flagByte | endianByte & flag::getByte(Flag::Endianess);
        bytes.putByte(flagByte);
        // SRID
        int srid = geometry->getSrid().empty() ? -1 : std::atoi(geometry->getSrid().c_str());
        bytes.putInt(srid);
        // Envelope
        if (envelopeType != EnvelopeType::NoEnvelope) {
            Bounds bounds = Bounds::getBounds(geometry);
            bytes.putDouble(bounds.getMinX());
            bytes.putDouble(bounds.getMaxX());
            bytes.putDouble(bounds.getMinY());
            bytes.putDouble(bounds.getMaxY());
            if (envelopeType == EnvelopeType::EnvelopeZ || envelopeType == EnvelopeType::EnvelopeZM) {
                bytes.putDouble(bounds.getMinZ());
                bytes.putDouble(bounds.getMaxZ());
            }
            if (envelopeType == EnvelopeType::EnvelopeM || envelopeType == EnvelopeType::EnvelopeZM) {
                bytes.putDouble(bounds.getMinM());
                bytes.putDouble(bounds.getMaxM());
            }
        }
        // Geometry
        std::vector<std::byte> geometryBytes = wkbWriter.write(geometry);
        bytes.putBytes(geometryBytes);
        return bytes;
    }

}

