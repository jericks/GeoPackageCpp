#pragma once

#include <iostream>

namespace geopackage {

    enum class EnvelopeType {
        NoEnvelope, Envelope, EnvelopeZ, EnvelopeM, EnvelopeZM
    };

    namespace envelopetype {

        std::string toString(EnvelopeType envelopeType);

        int getValue(EnvelopeType envelopeType);

        std::byte getByte(EnvelopeType envelopeType);

    }

    std::ostream& operator << (std::ostream& os, const EnvelopeType& envelopeType);

}