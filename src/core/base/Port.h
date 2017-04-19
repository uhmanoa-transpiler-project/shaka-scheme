#ifndef SHAKA_CORE_BASE_PORT_H
#define SHAKA_CORE_BASE_PORT_H

#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>

namespace shaka {

class Port {
public:
    enum class Mode : int {
        TEXT,
        BINARY
    };

    enum class Type : int {
        INPUT,
        OUTPUT
    };

    enum class Source : int {
        STRING,
        FILESTREAM
    };

    Port (std::string   str,
          Mode          mode,
          Type          type,
          Source        source) :
        mode(mode),
        type(type),
        source(source) {
        
        std::ios_base::openmode modeflag;
        if (type == Type::INPUT) {
            modeflag = std::fstream::in;
        }
        else {
            modeflag = std::fstream::out;
        }

        if (mode == Mode::BINARY) {
            modeflag |= std::fstream::binary;
        }

        if (source == Source::FILESTREAM && type == Type::INPUT) {
            this->in = std::move(std::unique_ptr<std::istream>(
                new std::ifstream(str.c_str(), modeflag)
            )); 
        }
        else if (source == Source::FILESTREAM && type == Type::OUTPUT) {
            this->out = std::move(std::unique_ptr<std::ostream>(
                new std::ofstream(str.c_str(), modeflag)
            )); 
        }
        else if (source == Source::STRING && type == Type::INPUT) {
            this->in = std::move(std::unique_ptr<std::istream>(
                new std::istringstream(str.c_str())
            )); 
        }
        else if (source == Source::STRING && type == Type::OUTPUT) {
            this->out = std::move(std::unique_ptr<std::ostream>(
                new std::ostringstream(str.c_str())
            )); 
        }
        else {
            throw std::runtime_error("Blah blah Port.h");
        }
    }

    ~Port() {
        if (source == Source::FILESTREAM && type == Type::INPUT) {
            dynamic_cast<std::ifstream*>(this->in.get())->close();
        }
        else if (source == Source::FILESTREAM && type == Type::OUTPUT) {
            dynamic_cast<std::ofstream*>(this->out.get())->close();
        }
    }

    Port::Mode get_mode() const {
        return this->mode;
    }

    Port::Type get_type() const {
        return this->type;
    }

    Port::Source get_source_type() const {
        return this->source;
    }

    union {
        std::unique_ptr<std::istream> in;
        std::unique_ptr<std::ostream> out;
    };
    const Mode mode;
    const Type type;
    const Source source;
};

}

#endif
