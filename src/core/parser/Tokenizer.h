#ifndef SHAKA_PARSER_TOKENIZER_H
#define SHAKA_PARSER_TOKENIZER_H

#include "core/parser/Token.h"

#include <iostream>
#include <string>
#include <deque>

#ifndef DEBUG_PRINT
#define DEBUG_PRINT 0
#else
#define DEBUG_PRINT 1
#endif

namespace shaka {

class Tokenizer {
private:
    std::istream&     in;
    std::deque<Token> tokens;
    bool              is_stopped;
public:
    Tokenizer (std::istream& in) :
        in(in),
        is_stopped(false) {}

    void stop () {
        is_stopped = true;
    }

    bool is_done () const {
        return is_stopped;
    }

    Token get () {
        if (!tokens.empty()) {
            auto front = tokens.front();
            tokens.pop_front();
            return front;
        } else {
            try {
                this->read_next_token();
            } catch (const char* c) {
                std::cerr << c << std::endl;
                throw c;
            }
            auto front = tokens.front();
            tokens.pop_front();
            return front;
        }
    }

    Token peek () {
        if (!tokens.empty()) {
            auto front = tokens.front();
            return front;
        } else {
            try {
                this->read_next_token();
            } catch (const char* c) {
                std::cerr << c << std::endl;
                throw c;
            }
            auto front = tokens.front();
            return front;
        }
    }

    void unget (Token t) {
        tokens.push_front(t);
    }

    void read_next_token () {
        Token t = parse_token();
        if (DEBUG_PRINT) {
            std::cerr << "Parsed: " << static_cast<int>(t.type)
            << " :: " << t.str << std::endl;
        }
        tokens.push_back(t); 
    }

    Token parse_paren_start() {
        // Begin parenthesis
        if (in.peek() == '(') {
            in.get();
            return Token(Token::Type::PAREN_START, "(");
        } else {
            throw std::runtime_error("Tokenizer: Could not parse Token.PAREN_START");
        }
    }

    Token parse_paren_end() {
        if (in.peek() == ')') {
            in.get();
            return Token(Token::Type::PAREN_END, ")");
        } else {
            throw std::runtime_error("Tokenizer: Could not parse Token.PAREN_END");
        }
    }

    void parse_string_element(std::string& str) {
        if (in.peek() == '\\') {
            in.get();
            // what type of escape?
            if (std::isalpha(in.peek())) {
                // Any of the mnemonic escapes?
                if (in.peek() == 'a') {
                    in.get();
                    str += '\a';
                    return;
                } else if (in.peek() == 'b') {
                    in.get();
                    str += '\b';
                    return;
                } else if (in.peek() == 't') {
                    in.get();
                    str += '\t';
                    return;
                } else if (in.peek() == 'n') {
                    in.get();
                    str += '\n';
                    return;
                } else if (in.peek() == 'r') {
                    in.get();
                    str += '\r';
                    return;

                // If the first letter is 'x', then possibly hex digit
                } else if (in.peek() == 'x') {
                    in.get();

                    // If the next character is a hex digit,
                    // then go into hex scalar value.
                    if (is_hex_digit(in.peek())) {
                        Token result(Token::Type::INVALID);
                        if (parse_hex_scalar_value_character(result)) {
                            str += result.str;
                            return;
                        } else {
                            str += "x";
                        }

                    // Otherwise, it's just a literal 'x'
                    } else {
                        str += "x";
                        return;
                    }


                // Otherwise, it's going to either be a single character escape
                // or a named character escape.
                } else {
                    if (DEBUG_PRINT) {
                        std::cerr << "in single/named char escape" << std::endl;
                    }
                    std::string buffer;
                    while (!is_delimiter(in.peek()) && in.peek() != EOF) {
                        buffer += in.get();
                    }
                    if (DEBUG_PRINT) {
                        std::cerr << "buffer: " << buffer << std::endl;
                        std::cerr << "buffer.size(): " << buffer.size() << std::endl;
                    }
                    // If escape for whitespace, read in whitespace and then
                    // continue reading string elements.
                    if (std::isspace(in.peek()) && buffer.size() == 0) {
                        while (std::isspace(in.peek())) {
                            in.get();
                        }
                        return;

                    // named character escape?
                    } else if (buffer == "alarm") {
                        str += "\a";
                        return;
                    } else if (buffer == "backspace") {
                        str += "\b";
                        return;
                    } else if (buffer == "delete") {
                        str += "\x7F";
                        return;
                    } else if (buffer == "escape") {
                        str += "\x1B";
                        return;
                    } else if (buffer == "newline") {
                        str += "\n";
                        return;
                    } else if (buffer == "null") {
                        str += "\0";
                        return;
                    } else if (buffer == "return") {
                        str += "\r";
                        return;
                    } else if (buffer == "space") {
                        str += " ";
                        return;
                    } else if (buffer == "tab") {
                        str += "\t";
                        return;

                    // Otherwise, error!
                    } else {
                        throw "Parser.parse_token: Bad character escape";
                        return;
                    }
                } // character escape
            // Else, literal " or etc.
            } else if (in.peek() == '\"') {
                in.get();
                str += "\"";
                return;
            } else {
                str += in.peek();
                in.get();
            }
        } else {
            str += in.peek();
            in.get();
        }
    }

    Token parse_string() {
        // String
        if (in.peek() == '\"') {
            in.get();
            // Read in the rest of the string.
            std::string buffer;
            while (in.peek() != '\"') {
                parse_string_element(buffer);
            } in.get();
            return Token(Token::Type::STRING, buffer);
        } else {
            throw std::runtime_error("Tokenizer: Could not parse Token.STRING");
        }
    }

    void parse_line_comment() {
        if (DEBUG_PRINT) {
            std::cout << "What LINE COMMENT is this? \'" <<
                in.peek() << "\'" << std::endl;
        }
        // If it's a comment, read until the
        // end of the lie.
        while (in.peek() != '\n') {
            in.get();
        } in.get();
    }

    bool parse_hex_scalar_value_character(Token& result) {
        if (is_hex_digit(in.peek())) {
            std::string buffer;
            while(is_hex_digit(in.peek())) {
                buffer += in.get();
            }
            int i = std::stoi(buffer, 0, 16);
            buffer.clear();
            buffer += static_cast<char>(i);
            result = Token(Token::Type::CHARACTER, buffer);
            return true;
        } else {
            throw std::runtime_error("Tokenizer: Could not parse CHARACTER.hex_scalar_value");
        }
    }

    bool parse_bytevector_byte(std::string& str) {
        if (std::isdigit(in.peek())) {
            std::string buffer;
            while (std::isdigit(in.peek())) {
                buffer += in.get();
            }
            int num = std::stoi(buffer);
            if (num >= 0 && num <= 255) {
                str += buffer;
                return true;
            } else {
                if (DEBUG_PRINT) {
                    std::cerr << "Parser.parse_bytevector_byte: Not in range [0, 255]" << std::endl;
                }
                throw std::runtime_error("Parser.parse_bytevector_byte: Not in range [0, 255]");
                return false;
            }

        } else {
            if (DEBUG_PRINT) {
                std::cerr << "Parser.parse_bytevector_byte: Not a digit" << std::endl;
            }
            throw std::runtime_error("Parser.parse_bytevector_byte: Not a digit");
            return false;
        }
    }

    bool rule_hash(Token& result) {
        if (in.peek() == '#') {
            in.get();

            // vector start token
            if (in.peek() == '(') {
                in.get();
                result = Token(Token::Type::VECTOR_START, "#(");
                return true;

            // <bytevector> ==> #u8( <byte>* )
            // Just read in the start token.
            } else if (in.peek() == 'u') {
                in.get();
                if (in.peek() == '8') {
                    in.get();
                    if (in.peek() == '(') {
                       in.get(); 
                       result = Token(Token::Type::BYTEVECTOR_START, "#u8(");
                       return true;
                    }
                } else {
                    if (DEBUG_PRINT) {
                        std::cerr << "bytevector: failed to read in 8 after u" << std::endl;
                    }
                    throw std::runtime_error("Parser.rule_hash: bytevector invalid prefix");
                    return false;
                }

            // <character>
            } else if (in.peek() == '\\') {
                in.get();
                if (DEBUG_PRINT) {
                    std::cerr << "in character" << std::endl;
                }

                // what type of escape?
                if (std::isalpha(in.peek())) {
                    // If the first letter is 'x', then possibly hex digit
                    if (in.peek() == 'x') {
                        in.get();

                        // If the next character is a hex digit,
                        // then go into hex scalar value.
                        if (is_hex_digit(in.peek())) {
                            return parse_hex_scalar_value_character(result);

                        // Otherwise, it's just a literal 'x'
                        } else {
                            result = Token(Token::Type::CHARACTER, "x"); 
                            return true;
                        }

                    // Otherwise, it's going to either be a single character escape
                    // or a named character escape.
                    } else {
                        if (DEBUG_PRINT) {
                            std::cerr << "in single/named char escape" << std::endl;
                        }
                        std::string buffer;
                        while (!is_delimiter(in.peek()) && in.peek() != EOF) {
                            buffer += in.get();
                        }
                        if (DEBUG_PRINT) {
                            std::cerr << "buffer: " << buffer << std::endl;
                            std::cerr << "buffer.size(): " << buffer.size() << std::endl;
                        }
                        // single character escape?
                        if (buffer.size() == 1) {
                            result = Token(Token::Type::CHARACTER, buffer);

                        // named character escape?
                        } else if (buffer == "alarm") {
                            result = Token(Token::Type::CHARACTER, "\a");
                            return true;
                        } else if (buffer == "backspace") {
                            result = Token(Token::Type::CHARACTER, "\b");
                            return true;
                        } else if (buffer == "delete") {
                            result = Token(Token::Type::CHARACTER, "\x7F");
                            return true;
                        } else if (buffer == "escape") {
                            result = Token(Token::Type::CHARACTER, "\x1B");
                            return true;
                        } else if (buffer == "newline") {
                            result = Token(Token::Type::CHARACTER, "\n");
                            return true;
                        } else if (buffer == "null") {
                            result = Token(Token::Type::CHARACTER, "\0");
                            return true;
                        } else if (buffer == "return") {
                            result = Token(Token::Type::CHARACTER, "\r");
                            return true;
                        } else if (buffer == "space") {
                            result = Token(Token::Type::CHARACTER, " ");
                            return true;
                        } else if (buffer == "tab") {
                            result = Token(Token::Type::CHARACTER, "\t");
                            return true;

                        // Otherwise, error!
                        } else {
                            throw "Parser.parse_token: Bad character escape";
                            result = Token(Token::Type::END_OF_FILE);
                            return false;
                        }
                    } // character escape
                }

            // <boolean> #t or #true? 
            } else if (in.peek() == 't') {

                std::string buffer;
                while (std::isalpha(in.peek())) {
                    buffer += in.get();
                }
                if (buffer == "true" || buffer == "t") {
                    result = Token(Token::Type::BOOLEAN_TRUE, "#t");
                    return true;
                } else {
                    throw "Parser.parse_token: invalid hash identifier/boolean does not match to true";
                    result = Token(Token::Type::END_OF_FILE);
                    return false;
                }
            // <boolean> #f or #false? 
            } else if (in.peek() == 'f') {
                std::string buffer;
                while (std::isalpha(in.peek())) {
                    buffer += in.get();
                }
                if (buffer == "false" || buffer == "f") {
                    result = Token(Token::Type::BOOLEAN_FALSE, "#f");
                    return true;
                } else {
                    throw "Parser.parse_token: invalid hash identifier/boolean does not match to true";
                    result = Token(Token::Type::END_OF_FILE);
                    return false;
                }
            // Nested comment must keep track
            // of depth.
            } else if (in.peek() == '|') {
                int depth_count = 1;
                while (depth_count > 0) {
                    if (in.peek() == '|') {
                        in.get();
                        if (in.peek() == '#') {
                            in.get();
                            depth_count--;
                        }
                    } else if (in.peek() == '#') {
                        in.get();
                        if (in.peek() == '|') {
                            in.get();
                            depth_count++;
                        }
                    } else {
                        if (DEBUG_PRINT) {
                            std::cerr << "What is this? \'" << in.peek()
                                << "\'" << std::endl;
                        }
                        in.get();
                    }
                }
                return false;

            // Single datum comment.
            } else if (in.peek() == ';') {
                in.get();
                result = Token(Token::Type::DATUM_COMMENT, "#;");
                return true;

            // Directive
            } else if (in.peek() == '!') {
                in.get();
                
                // Read in the directive string.
                std::string buffer;
                while (!is_delimiter(in.peek())) {
                    buffer += in.get(); 
                }
                // fold-case directive?
                if (buffer == "fold-case") {
                    result = Token(Token::Type::DIRECTIVE, "fold-case");
                    return true;
                // no-fold-case directive?
                } else if (buffer == "no-fold-case") {
                    result = Token(Token::Type::DIRECTIVE, "no-fold-case");
                    return true;
                } else {
                    if (DEBUG_PRINT) {
                        std::cerr << "BROKE ON: " << in.peek() << std::endl;
                    }
                    throw "Parser.parse_token: invalid directive";
                    result = Token(Token::Type::END_OF_FILE);
                    return false;
                }
            } else {
                if (DEBUG_PRINT) {
                    std::cerr << "BROKE ON: " << in.peek() << std::endl;
                }
                throw "Parser.parse_token: invalid hash directive";
                result = Token(Token::Type::END_OF_FILE);
                return false;
            }
        } else {
            if (DEBUG_PRINT) {
                std::cerr << "BROKE ON: " << in.peek() << std::endl;
            }
            throw "Parser.parse_token: is not a hash? wrong";
            result = Token(Token::Type::END_OF_FILE);
            return false;
        }

        /// @todo Need to make sure why the compiler gives a
        ///       warning why it doesn't think it may
        ///       not return a value.
        return false;
    }

    Token parse_number(std::string& buffer) {

        bool number = false;
        // Parse sign if it's there
        if (is_explicit_sign(in.peek())) {
            buffer += in.get();
        }
        // Parse the integer part.
        while (std::isdigit(in.peek())) {
            buffer += in.get();

            number = true;
        }
	
        // Parse in a dot if it's a float
        if (in.peek() == '.') {
            buffer += in.get();

      	    // Parse in the fractional integer part.
     	    while (std::isdigit(in.peek())) {
            	buffer += in.get();
       	    }

            number = true;
        } 
	
        // If there is a /, it is a fraction
        if (in.peek() == '/') {
            buffer += in.get();

            while (std::isdigit(in.peek())) {
            buffer += in.get();

            number = true;
	    }

	}

	// If the next character is not a space,
	// like possibly an alpha character, that's not right.
	if (!std::isspace(in.peek())
	    && !in.eof()
            && in.peek() != ';'
            && in.peek() != ')') {
		number = false;
	}

        //
        //  // Make sure that it's the end of the number
        //  if (is_delimiter(in.peek())) {
        //      return Token(Token::Type::NUMBER, buffer);
        //  } else {
        //      if (DEBUG_PRINT) {
        //          std::cerr << "Tokenizer.parse_number: Did not find following delimiter" << std::endl;
        //      }
        //      throw std::runtime_error("Tokenizer.parse_number: Did not find following delimiter");
        //      return Token(Token::Type::INVALID);
        //  }
        //

        if (number == true) {
            return Token(Token::Type::NUMBER, buffer);
	}
	else {
	    throw std::runtime_error("Tokenizer.parse_number: Is not a number");
	    return Token(Token::Type::INVALID, buffer);

    	}
    }
    Token parse_token () {
        bool done = false;
        while (!done) {
            // Quote
            if (in.peek() == '\'') {
                in.get();
                return Token(Token::Type::QUOTE, "\'");

            // Backtick
            } else if (in.peek() == '`') {
                in.get();
                return Token(Token::Type::BACKTICK, "`");

            // Comma
            } else if (in.peek() == ',') {
                in.get();
                // Comma at-sign.
                if (in.peek() == '@') {
                    in.get();
                    return Token(Token::Type::COMMA_ATSIGN, ",@");
                } else {
                    return Token(Token::Type::COMMA, ",");
                }


            } else if (in.peek() == '.') {
                in.get();
                return Token(Token::Type::PERIOD, ".");
            
            // Begin parenthesis
            } else if (in.peek() == '(') {
                return parse_paren_start();

            // End parenthesis
            } else if (in.peek() == ')') {
                return parse_paren_end();

            // String
            } else if (in.peek() == '\"') {
                return parse_string();

            // Line comment
            } else if (in.peek() == ';') {
                parse_line_comment();
                // Then, continue and get next token to parse.
                done = false;

            // End of file
            } else if (in.peek() == EOF) {
                if (DEBUG_PRINT) {
                    std::cerr << "What EOF is this? \'" << in.peek() << "\'" << std::endl;
                }
                in.get();
                return Token(Token::Type::END_OF_FILE);

            // Skip whitespace
            } else if (std::isspace(in.peek())) {
                if (DEBUG_PRINT) {
                    std::cerr << "What space is this? \'" << in.peek() << "\'" << std::endl;
                }
                in.get();
                done = false;

            // Comment or boolean begins with #
            } else if (in.peek() == '#') {
                Token result(Token::Type::END_OF_FILE);
                if (rule_hash(result)) {
                    return result;
                } else {
                    done = false;
                }

            // Identifier ==> <initial> <subsequent>*
            } else if (is_initial(in.peek())) {
                if (DEBUG_PRINT) {
                    std::cout << "What INITIAL is this? \'" << in.peek() << "\'" << std::endl;
                }
                std::string buffer;
                buffer += in.get();
                // Keep getting subsequent if needed.
                while (is_subsequent(in.peek())) {
                    buffer += in.get();
                }
                return Token(Token::Type::IDENTIFIER, buffer);

            // Identifier ==> <vertical line> <symbol element>* <vertical line>
            } else if (in.peek() == '|') {
                in.get();
                std::string buffer;
                while (handle_symbol_element(in, buffer));
                if (in.peek() == '|') {
                    in.get();
                    return Token(Token::Type::IDENTIFIER, buffer);
                } else {
                    throw "Parser.parse_token: invalid pipe-delimted identifier syntax";
                    return Token(Token::Type::END_OF_FILE);
                }

            // Identifier ==> <explicit sign> ...
            } else if (is_explicit_sign(in.peek())) {
                std::string buffer;
                buffer += in.get();
                // <sign subsequent> <subsequent>*
                if (is_sign_subsequent(in.peek())) {
                    buffer =+ in.get();
                    while (is_subsequent(in.peek())) {
                        buffer += in.get(); 
                    }
                    return Token(Token::Type::IDENTIFIER, buffer);
                // . <dot subsequent> <subsequent>*
                } else if (in.peek() == '.') {
                    buffer += in.get();
                    if (is_dot_subsequent(in.peek())) {
                        buffer += in.get();
                        while (is_subsequent(in.peek())) {
                            buffer += in.get(); 
                        }
                        return Token(Token::Type::IDENTIFIER, buffer);

                    // if it's a digit, it's probably a number
                    } else if (std::isdigit(in.peek())) {
                        return parse_number(buffer);
                        
                    // no <dot subsequent> ==> error!
                    } else {
                        throw "Parser.parse_token: bad dot subsequent identifier";
                        return Token(Token::Type::END_OF_FILE);
                    }

                // Parse in a number
                } else if (std::isdigit(in.peek())) {
                    std::string buffer;

                    //Unget to get back the sign
                    in.unget();

                    return parse_number(buffer);

                // No other identifier? Just <explicit sign> is fine.
                } else {
                    return Token(Token::Type::IDENTIFIER, buffer);
                }
            
            // Identifier ==> . <dot subsequent> <subsequent>
            } else if (in.peek() == '.') {
                std::string buffer;
                buffer += in.get();
                if (is_dot_subsequent(in.peek())) {
                    buffer += in.get();
                    while (is_subsequent(in.peek())) {
                        buffer += in.get();
                    }
                    return Token(Token::Type::IDENTIFIER, buffer);
                } else {
                    throw "Parser.parse_token: bad dot subsequent identifier";
                    return Token(Token::Type::END_OF_FILE);
                }

            // <number> ==> <num 10> for now
            /// @todo Add real, rational, complex for different radixes.
            } else if (std::isdigit(in.peek())) {
                std::string buffer;
                return parse_number(buffer);

            // NOT A VALID TOKEN!!!
            } else {
                if (DEBUG_PRINT) {
                    std::cerr << "BROKE ON: " << in.peek() << std::endl;
                }
                throw "Parser.parse_token: invalid token";
                return Token(Token::Type::END_OF_FILE);
            }
        }
        throw 1;
        return Token(Token::Type::END_OF_FILE);
    }

    bool is_delimiter(char c) {
        return (
            std::isspace(c)
            || c == '|'
            || c == '('
            || c == ')'
            || c == '\"'
            || c == ';'
        );
    }

    bool is_special_initial (char c) {
        return (
            c == '!' ||
            c == '$' ||
            c == '%' ||
            c == '&' ||
            c == '*' ||
            c == '/' ||
            c == '!' ||
            c == ':' ||
            c == '>' ||
            c == '=' ||
            c == '>' ||
            c == '?' ||
            c == '^' ||
            c == '_' ||
            c == '!'
        );
    }

    bool is_special_subsequent (char c) {
        return (
            c == '.'
            || c == '@'
            || is_explicit_sign(c)
        );
    }

    bool is_explicit_sign (char c) {
        return (c == '+' || c == '-');
    }

    bool is_letter (char c) {
        return (std::isalpha(c));
    }

    bool is_subsequent (char c) {
        return (is_initial(c)
            || is_digit(c)
            || is_special_subsequent(c));
    }

    bool is_initial (char c) {
        return (is_letter(c) || is_special_initial(c));
    }

    bool is_digit (char c) {
        return (std::isdigit(c));
    }

    bool handle_symbol_element(std::istream& in, std::string& interm) {

        // Terminating symbol
        if (in.peek() == '|') {
            return false;

        // Escape sequence
        } else if (in.peek() == '\\') {
            in.get();
            // inline_hex_escape?
            if (in.peek() == 'x') {
                in.get();
                return(handle_inline_hex_escape(in, interm));

            // mnemonic_escape?
            } else if (in.peek() == 'a') {
                in.get();
                interm += '\a';
                return true;
            } else if (in.peek() == 'b') {
                in.get();
                interm += '\b';
                return true;
            } else if (in.peek() == 't') {
                in.get();
                interm += '\t';
                return true;
            } else if (in.peek() == 'n') {
                in.get();
                interm += '\n';
                return true;
            } else if (in.peek() == 'r') {
                in.get();
                interm += '\r';
                return true;

            // escape for pipe character?
            } else if (in.peek() == '|') {
                in.get();
                interm += '|';
                return true;

            // otherwise, invalid!
            } else {
                throw "Parser.mnemonic_escape: invalid escape character";
                return false;
            }

        // Otherwise, just consume the next character.
        } else {
            interm += in.get();
            return true;
        }
    }

    bool is_dot_subsequent(char c) {
        return (is_sign_subsequent(c) || c == '.');
    }

    bool handle_inline_hex_escape(std::istream& in, std::string& interm) {
        char c = in.peek();
        std::string buffer;
        while (
            std::isdigit(c)
            || c == 'a'
            || c == 'b'
            || c == 'c'
            || c == 'd'
            || c == 'e'
            || c == 'f'
        ) {
            in.get(); 
            buffer += c;
            c = in.peek(); 
        }
        // Correct form ==> push character onto interm string.
        if (in.peek() == ';') {
            int i = std::stoi(buffer, 0, 16);
            interm += static_cast<char>(i);
            return true;

        // incorect form ==> error!
        } else {
            throw "Parser.handle_inline_hex_escape: no terminating \';\' character";
            return false;
        }
    }

    bool is_sign_subsequent(char c) {
        return (
            is_initial(c)
            || is_explicit_sign(c)
            || c == '@'
        );
    }

    bool is_hex_digit(char c) {
        return (
            std::isdigit(c)
            || c == 'a'
            || c == 'b'
            || c == 'c'
            || c == 'd'
            || c == 'e'
            || c == 'f'
        );
    }
};

} // namespace shaka

#endif // SHAKA_PARSER_TOKENIZER_H
