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

    Mode mode;
    Type type;
};

}

#endif
