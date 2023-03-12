#include "GeoPackageGeometryReader.hpp"

namespace geopackage {

    std::unique_ptr<Geometry> GeoPackageGeometryReader::read(std::vector<std::byte> bytes) {

        // Magic
        std::byte magic1 = bytes[0];
        std::byte magic2 = bytes[1];

        // Version
        int version = std::to_integer<int>(bytes[2]);

        // Flags
        std::byte flags = bytes[3];
        int binaryType = std::to_integer<int>(flags & flag::getByte(Flag::BinaryType));
        int emptyGeometry = std::to_integer<int>(flags & flag::getByte(Flag::GeometryEmpty));
        int envelopeIndicator = std::to_integer<int>(flags & flag::getByte(Flag::EnvelopeIndicator)) >> 1;
        EnvelopeType envelopeType = envelopetype::getEnvelopeType(envelopeIndicator);
        int endianess = std::to_integer<int>(flags & flag::getByte(Flag::Endianess));
        Endian endian = endianess == 0 ? Endian::BIG : Endian::LITTLE;

        Bytes _bytes {endian, bytes};
        _bytes.setPosition(4);

        // SRID 
        int srsId = _bytes.getInt();

        // Envelope
        std::optional<Bounds> bounds;
        if (envelopeType != EnvelopeType::NoEnvelope) {
            double minX = _bytes.getDouble();
            double maxX = _bytes.getDouble();
            double minY = _bytes.getDouble();
            double maxY = _bytes.getDouble();
            double minZ = NAN;
            double maxZ = NAN;
            double minM = NAN;
            double maxM = NAN;
            if (envelopetype::hasZ(envelopeType)) {
                minZ = _bytes.getDouble();
                maxZ = _bytes.getDouble();
            }
            if (envelopetype::hasM(envelopeType)) {
                minM = _bytes.getDouble();
                maxM = _bytes.getDouble();
            }
            bounds = Bounds{minX, minY, minZ, minM, maxX, maxY, maxZ, maxM};
        }

        WKBReader wkbReader;
        std::unique_ptr<Geometry> geometry = wkbReader.read(_bytes);
        return geometry;
    }

}