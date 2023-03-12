#pragma once

#include <iostream>

namespace geopackage {

    enum class EnvelopeType {
        NoEnvelope, Envelope, EnvelopeZ, EnvelopeM, EnvelopeZM
    };

    namespace envelopetype {

        std::string toString(EnvelopeType envelopeType);

        int getValue(EnvelopeType envelopeType);

        EnvelopeType getEnvelopeType(int value);

        std::byte getByte(EnvelopeType envelopeType);

        bool hasM(EnvelopeType envelopeType);

        bool hasZ(EnvelopeType envelopeType);

    }

    std::ostream& operator << (std::ostream& os, const EnvelopeType& envelopeType);

}