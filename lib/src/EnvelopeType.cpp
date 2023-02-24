#include "EnvelopeType.hpp"

namespace geopackage {

    namespace envelopetype {

        std::string toString(EnvelopeType envelopeType) {
            if (envelopeType == EnvelopeType::NoEnvelope) {
                return "NoEnvelope";
            } else if (envelopeType == EnvelopeType::Envelope) {
                return "Envelope";
            } else if (envelopeType == EnvelopeType::EnvelopeZ) {
                return "EnvelopeZ";
            } else if (envelopeType == EnvelopeType::EnvelopeM) {
                return "EnvelopeM";
            } else if (envelopeType == EnvelopeType::EnvelopeZM) {
                return "EnvelopeZM";
            } else {
                return "";
            }
        }

        int getValue(EnvelopeType envelopeType) {
            if (envelopeType == EnvelopeType::NoEnvelope) {
                return 0;
            } else if (envelopeType == EnvelopeType::Envelope) {
                return 1;
            } else if (envelopeType == EnvelopeType::EnvelopeZ) {
                return 2;
            } else if (envelopeType == EnvelopeType::EnvelopeM) {
                return 3;
            } else if (envelopeType == EnvelopeType::EnvelopeZM) {
                return 4;
            } else {
                return -1;
            }
        }

        std::byte getByte(EnvelopeType envelopeType) {
            if (envelopeType == EnvelopeType::NoEnvelope) {
                return std::byte{0};
            } else if (envelopeType == EnvelopeType::Envelope) {
                return std::byte{1};
            } else if (envelopeType == EnvelopeType::EnvelopeZ) {
                return std::byte{2};
            } else if (envelopeType == EnvelopeType::EnvelopeM) {
                return std::byte{3};
            } else if (envelopeType == EnvelopeType::EnvelopeZM) {
                return std::byte{4};
            } else {
                return std::byte{};
            }
        }
    }

    

    std::ostream& operator << (std::ostream& os, const EnvelopeType& envelopeType) {
        os << envelopetype::toString(envelopeType);
        return os;
    }

}