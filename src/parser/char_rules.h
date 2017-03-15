#ifndef SHAKA_PARSER_RULE_CHAR_RULES_H
#define SHAKA_PARSER_RULE_CHAR_RULES_H

#include <cctype>
#include <vector>
#include <functional>

#include "parser/primitives.h"
#include "parser/logic_rules.h"

namespace shaka {
namespace parser {
namespace rule {


/// @brief Matches a digit character, and then appends it to
///        `interm`.
template <typename T>
bool digit(
    InputStream&    in,
    NodePtr         root,
    T&              interm
) {
    if (std::isdigit(in.peek())) {
        interm += in.get();
        return true;        
    } else {
        return false;
    }
}


/// @brief Matches an alpha character, and then
///        appends it to `interm`.
template <typename T>
bool alpha(
    InputStream&    in,
    NodePtr         root,
    T&              interm
) {
    if (std::isalpha(in.peek())) {
        interm += in.get();
        return true;        
    } else {
        return false;
    }
}

/// @brief Matches an alpha character, and then
///        appends it to `interm`.
template <typename T>
bool space(
    InputStream&    in,
    NodePtr         root,
    T&              interm
) {
    if (std::isspace(in.peek())) {
        interm += in.get();
        return true;        
    } else {
        return false;
    }
}

template <typename T, const char C>
bool match_char(
    InputStream&    in,
    NodePtr         root,
    T&              interm
) {
    if (in.peek() == C) {
        interm += in.get();
        return true;
    } else {
        return false;
    }
}


/// @brief Matches a hex digit character, and then appends it to
///        `interm`.
template <typename T>
bool hex_digit(
    InputStream&    in,
    NodePtr         root,
    T&              interm
) {
    if (in.peek() == 'a' ||
        in.peek() == 'b' ||
        in.peek() == 'c' ||
        in.peek() == 'd' ||
        in.peek() == 'e' ||
        in.peek() == 'f'  ) {
        interm += in.get();
        return true;

    } else if ( digit(in, root, interm) ) {
        return true;
    } else {
        return false;
    }
}


/// @brief Matches a special initial character, and then
///        appends it to 'interm'
template <typename T>
bool special_initial(
    InputStream&    in,
    NodePtr         root,
    T&              interm
) {
    bool found;
    switch(in.peek()) {
        case '!':
        case '$':
        case '%':
        case '&':
        case '*':
        case '/':
        case ':':
        case '<':
        case '=':
        case '>':
        case '?':
        case '^':
        case '_':
        case '~':
            found = true;
            break;
        default:
            found = false;
            break;
    }

    if (found) {
        interm += in.get();
        return true;        
    } else {
        return false;
    }
}

/// @brief Matches an initial character, and then appends 
///        it to 'interm'
template <typename T>
bool initial(
    InputStream&    in,
    NodePtr         root,
    T&              interm
) {
    // letter or special initial
    // alpha or special_initial
    std::vector<std::function<bool(InputStream&, NodePtr, T&)>> rules;
    rules.push_back(alpha<T>);
    rules.push_back(special_initial<T>);

    if (rules_or<T>(in, root, interm, rules)) {
        return true;        
    } else {
        return false;
    }
}


/// @brief Matches an explicit sign character ( + or -),
///        and then appends it to 'interm'
template <typename T>
bool explicit_sign(
    InputStream&    in,
    NodePtr         root,
    T&              interm
) {

    if (in.peek() == '+' || in.peek() == '-') {
        interm += in.get();
        return true;        
    } else {
        return false;
    }
}

/// @brief Matches a special_subsequent character
///        and then appends it to 'interm'
template <typename T>
bool special_subsequent(
    InputStream&    in,
    NodePtr         root,
    T&              interm
) {
    if (in.peek() == '+' ||
        in.peek() == '-' ||
        in.peek() == '.' ||
        in.peek() == '@'   ) {

        interm += in.get();
        return true;        
    } else {
        return false;
    }
}

/// @brief Matches a sign_subsequent character
///        and then appends it to 'interm'
template <typename T>
bool sign_subsequent(
    InputStream&    in,
    NodePtr         root,
    T&              interm
) {
    if ( initial<T>(in, root, interm) ) {
        return true;        
    } else if (in.peek() == '+' ||
               in.peek() == '-' ||
               in.peek() == '@'  ) {
        interm += in.get();
        return true;
    } else {
        return false;
    }
}

/// @brief Matches a dot_subsequent character
///        and then appends it to 'interm'
template <typename T>
bool dot_subsequent(
    InputStream&    in,
    NodePtr         root,
    T&              interm
) {
    if ( sign_subsequent<T>(in, root, interm) ) {
        return true;        
    } else if ( in.peek() == '.' ) {
        interm += in.get();
        return true;
    } else {
        return false;
    }
}

/// @brief Matches a subsequent character
///        and then appends it to 'interm'
template <typename T>
bool subsequent(
    InputStream&    in,
    NodePtr         root,
    T&              interm
) {

    // initial or digit or special subsequent
    // initial / digit / special_subsequent
    std::vector<std::function<bool(InputStream&, NodePtr, T&)>> rules;
    rules.push_back(initial<T>);
    rules.push_back(digit<T>);
    rules.push_back(special_subsequent<T>);
    
    if (rules_or<T>(in, root, interm, rules)) {
        return true;        
    } else {
        return false;
    }
}


} // namespace rule
} // namespace parser
} // namespace shaka


#endif // SHAKA_PARSER_RULE_CHAR_RULES_H
