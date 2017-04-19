#ifndef SHAKA_CORE_BASE_PORT_H
#define PORT_H

#include <iostream>
#include <exception>

namespace shaka {

class Port {
public:
    Port (Port::Mode mode,
          Port::Type type) :
        mode(mode),
        type(type) {}

    enum class Mode : int {
        TEXT,
        BINARY
    };
    enum class Type : int {
        INPUT,
        OUPTUT
    };

    Port::Mode get_mode() const {
        return this->mode;
    }

    Port::Type get_type() const {
        return this->type;
    }

    Mode mode;
    Type type;
};

}

#endif
