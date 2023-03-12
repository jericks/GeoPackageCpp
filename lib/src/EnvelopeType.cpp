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

        EnvelopeType getEnvelopeType(int value) {
            if (value == 0) {
                return EnvelopeType::NoEnvelope;
            } else if (value == 1) {
                return EnvelopeType::Envelope;
            } else if (value == 2) {
                return EnvelopeType::EnvelopeZ;
            } else if (value == 3) {
                return EnvelopeType::EnvelopeM;
            } else if (value == 4) {
                return EnvelopeType::EnvelopeZM;
            } else {
                return EnvelopeType::NoEnvelope;
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

        bool hasM(EnvelopeType envelopeType) {
            if (envelopeType == EnvelopeType::EnvelopeM || envelopeType == EnvelopeType::EnvelopeZM) {
                return true;
            } else {
                return false;
            }
        }

        bool hasZ(EnvelopeType envelopeType) {
            if (envelopeType == EnvelopeType::EnvelopeZ || envelopeType == EnvelopeType::EnvelopeZM) {
                return true;
            } else {
                return false;
            }
        }
        
    }

    std::ostream& operator << (std::ostream& os, const EnvelopeType& envelopeType) {
        os << envelopetype::toString(envelopeType);
        return os;
    }

}