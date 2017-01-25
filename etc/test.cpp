
#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>

#include "SExpression.h"




namespace shaka {
namespace rules {

class Parser {
public:
    ~Parser() {}

    Parser(std::function<void(std::istream&, SExpression&)> func) = 0;

private:
    std::function<void(std::istream&, SExpression&)> func;
};


// string = alpha+
auto string = [](std::istream& in, SExpression& out) -> void {
    char c = '\0';
    std::string buf;

    // Check that the first character is a string.
    c = in.peek();
    if (std::isalpha(c)) {
        buf += c;
        // While the input is still alpha characters,
        // continue to add onto the buffer.
        do {
            c = in.peek();
            // Once done, output to the data, and then return.
            if (!std::isalpha(c)) {
                out = String(buf);
                return;
            } else {
                buf += c;
                in.get();
            }
        } while (true);
    } else {
        throw std::runtime_error("is_string: failed to recognize at least 1 string");
    }
};

auto whitespace = [](std::istream& in, SExpression& out) -> void {
    while (in.good()) {
        if (!std::isspace(in.get())) {
            return;
        }
    }
    throw std::runtime_error("is_whitespace: input stream is not in good condition.");
};

// number = digit+
// digit = is_digit(c)
auto number = [](std::istream& in, SExpression& out) -> void {
    char c = '\0';
    std::string buf;

    // Check that the first character is a digit.
    c = in.peek();
    if (std::isdigit(c)) {
        buf += c;
        // While the character is still a digit, continue to add onto the buffer.
        do {
            c = in.peek();
            // Once done, output to the data, and then return.
            if (!std::isdigit(c)) {
                out = Number(std::stoi(buf));
                return;
            } else {
                buf += c;
                in.get();
            }
        } while (true);
    // If it's not, then it's an error.
    } else {
        throw std::runtime_error("is_number: failed to recognize at least 1 digit");
    }
};

auto list = [](std::istream& in, SExpression& out) {
    char c = '\0';
    std::string buf;

    // Check if the first character is a (
    c = in.peek();
    if (c == '(') {
        buf += c;
        // Parse numbers or digits
        out = std::vector<SExpression>();

        while (in.peek() != ')') {
            
        }
    }
};


auto expect = [](std::function<void(std::istream&, SExpression&)>  func,
                 std::istream&                                     in,
                 SExpression&                                      out) -> void {
    if (in.good()) {
        func(in, out);
    } else {
        throw std::runtime_error("expect: input stream is not in good condition.");
    }
};

auto ignore = [](std::function<void(std::istream&, SExpression&)>  func,
                 std::istream&                                     in) -> void {
    if (in.good()) {
        SExpression temp;
        func(in, temp);
    } else {
        throw std::runtime_error("expect: input stream is not in good condition.");
    }
};

auto parse_or = [](std::vector<std::function<void(std::istream&, SExpression&)>> func,
                   std::istream&                                                 in) -> void {
    if (in.good()) {

    }
}

} // namespace rules
} // namespace shaka

int main(int argc, char** argv) {
    try {
        if (argc == 2) {
            std::ifstream filein(argv[1]);
            // If the file is good, begin parsing.
            if (filein.good()) {

                using namespace shaka;
                using namespace shaka::rules;
                SExpression n;
                expect(number, filein, n);
                std::cout << n << std::endl;

                ignore(whitespace, filein);

                SExpression m;
                expect(string, filein, m);
                std::cout << m << std::endl;
            } else {
                std::string str;
                str += std::string(argv[1]) + " is not a valid input file.";
                throw std::runtime_error(str);
            }
        } else {
            std::string str;
            str += std::string(argv[0]) + " was not given the right amount of "
                "arguments.";
            throw std::runtime_error(str);
        }
    } catch (std::exception& e) {
        std::cout << "ERROR: " << e.what() << std::endl;
    }
}