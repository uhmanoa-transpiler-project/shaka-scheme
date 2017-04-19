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
        std::cout << "Modeflag: setting done." << std::endl;

        if (source == Source::FILESTREAM && type == Type::INPUT) {
            std::cout << "FILESTREAM INPUT" << std::endl;
            this->in = new std::ifstream(str.c_str(), modeflag);
            std::cout << "FILESTREAM INPUT" << std::endl;
        }
        else if (source == Source::FILESTREAM && type == Type::OUTPUT) {
            std::cout << "FILESTREAM OUTPUT" << std::endl;
            this->out = new std::ofstream(str.c_str(), modeflag);
            std::cout << "FILESTREAM OUTPUT" << std::endl;
        }
        else if (source == Source::STRING && type == Type::INPUT) {
            std::cout << "STRING INPUT" << std::endl;
            this->in = new std::istringstream(str.c_str());
            std::cout << "STRING INPUT" << std::endl;
        }
        else if (source == Source::STRING && type == Type::OUTPUT) {
            std::cout << "STRING OUTPUT" << std::endl;
            this->out =  new std::ostringstream(str.c_str());
            std::cout << "STRING OUTPUT" << std::endl;
        }
        else {
            throw std::runtime_error("Blah blah Port.h");
        }
    }

    ~Port() {
        std::cout << "~Port()" << std::endl;
        if (source == Source::FILESTREAM && type == Type::INPUT) {
            auto* ptr = dynamic_cast<std::ifstream*>(this->in);
            ptr->close();
            delete ptr;
        }
        else if (source == Source::FILESTREAM && type == Type::OUTPUT) {
            auto* ptr = dynamic_cast<std::ofstream*>(this->out);
            ptr->close();
            delete ptr;
        }
        else if (source == Source::STRING && type == Type::INPUT) {
            delete dynamic_cast<std::istringstream*>(this->in);
        }
        else if (source == Source::STRING && type == Type::OUTPUT) {
            delete dynamic_cast<std::ostringstream*>(this->out);
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

    std::istream* in;
    std::ostream* out;
    const Mode mode;
    const Type type;
    const Source source;
};

}

#endif
