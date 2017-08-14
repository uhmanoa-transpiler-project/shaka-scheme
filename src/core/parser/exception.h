#ifndef SHAKA_CORE_PARSER_EXCEPTION_H
#define SHAKA_CORE_PARSER_EXCEPTION_H

#include <exception>

namespace shaka {
namespace parser {

class end : std::exception {
public:
    end() { }
};

}
}

#endif // SHAKA_CORE_PARSER_EXCEPTION_H
