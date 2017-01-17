
#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>

#include <boost/variant.hpp>

// number = digit+
// digit = is_digit(c)


// string = alpha+
// program = string | number

using Node = boost::make_recursive_variant<
    int,
    std::string,
    std::vector<boost::recursive_variant_>
>::type;

std::ostream& operator<<(std::ostream& lhs, std::vector<Node> rhs) {
    lhs << "(";
    for (auto& it : rhs) {
        lhs << ' ' << it;
    }
    lhs << " )";
    return lhs;
}

namespace Rules {


auto string = [](std::istream& in, Node& out) -> void {
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
                out = buf;
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

auto whitespace = [](std::istream& in, Node& out) -> void {
    while (in.good()) {
        if (!std::isspace(in.get())) {
            return;
        }
    }
    throw std::runtime_error("is_whitespace: input stream is not in good condition.");
};

auto number = [](std::istream& in, Node& out) -> void {
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
                out = std::stoi(buf);
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

auto list = [](std::istream& in, Node& out) {};

} // namespace Rules

auto expect = [](std::function<void(std::istream&, Node&)>  func,
                 std::istream&                              in,
                 Node&                                      out) -> void {
    if (in.good()) {
        func(in, out);
    } else {
        throw std::runtime_error("expect: input stream is not in good condition.");
    }
};

auto ignore = [](std::function<void(std::istream&, Node&)>  func,
                 std::istream&                              in) -> void {
    if (in.good()) {
        Node temp;
        func(in, temp);
    } else {
        throw std::runtime_error("expect: input stream is not in good condition.");
    }
};


// expect
// ignore

int main(int argc, char** argv) {
    try {
        if (argc == 2) {
            std::ifstream filein(argv[1]);
            // If the file is good, begin parsing.
            if (filein.good()) {

                using namespace Rules;
                Node n;
                expect(number, filein, n);
                std::cout << n << std::endl;

                ignore(whitespace, filein);

                Node m;
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