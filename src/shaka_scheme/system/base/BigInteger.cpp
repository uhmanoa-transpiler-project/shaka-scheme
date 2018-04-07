//
// Created by Jared Shimabukuro on 3/3/18.
//

#include "shaka_scheme/system/base/jshima_BigInteger.hpp"
#include "shaka_scheme/system/base/Rational.hpp"
#include "shaka_scheme/system/base/Real.hpp"

namespace shaka {

    BigInteger::BigInteger() :
    str_value("0") {
        this->value.push_back(0);
    }

    BigInteger::BigInteger(const BigInteger& other) :
	value(other.value), str_value(other.str_value) {}

    BigInteger::BigInteger(std::string val) :
    str_value(val) {
        for(std::int64_t i = (val.length()); i > 0; i-= 18) {
            if(i < 18) {
                if (val[0] == '-') {
                    sign = true;
                    this->value.insert(this->value.begin(), std::stoull(val.substr(1, (i-1))));
                }

                else {
                    sign = false;
                    this->value.insert(this->value.begin(), std::stoull(val.substr(0,i)));
                }
            }

            else
                this->value.insert(this->value.begin(), std::stoull(val.substr((i-18),18)));
        }
    }

    BigInteger::BigInteger(bool s, std::vector<std::uint64_t> val) :
    value(val) {
        if (s) {
            sign = true;
            this->str_value = "-";
        }
        else {
            sign = false;
            this->str_value = "";
        }


        for(int i = 0; i < val.size(); i++) {
            this->str_value.append(std::to_string(val[i]));
        }
    }

    BigInteger::operator Rational() {
        /*************************************************/
        /*************************************************/
        /*** FIGURE OUT HOW TO IMPLEMENT THIS FUNCTION ***/
        /*************************************************/
        /*************************************************/
    }

    /**
     * @todo Test the conversion from BigInteger to Real
     */
    BigInteger::operator Real() {
        double result;
        return result;
    }

    BigInteger operator+(const BigInteger& lhs, const BigInteger& rhs) {
        BigInteger result;

        /**
         * @todo Implement the Parallel Algorithm (Preferred):
         * https://arxiv.org/ftp/arxiv/papers/1204/1204.0232.pdf
         *
         * Reference to C++ thread commands:
         * http://en.cppreference.com/w/c/thread
         */

        /**
         * @todo Or Implement the Sequential Algorithm (Backup Plan):
         * https://arxiv.org/ftp/arxiv/papers/1204/1204.0232.pdf
         */

        /**
         * @todo Or Implement the Math-by-Hand Method (Last Resort):
         * https://silentmatt.com/blog/2011/10/how-bigintegers-work/
         */

        return result;
    }

    BigInteger operator-(const BigInteger& lhs, const BigInteger& rhs) {
        BigInteger result;

        /**
         * @todo Implement the Parallel Algorithm (Preferred):
         * https://arxiv.org/ftp/arxiv/papers/1204/1204.0232.pdf
         *
         * Reference to C++ thread commands:
         * http://en.cppreference.com/w/c/thread
         */

        /**
         * @todo Or Implement the Sequential Algorithm (Backup Plan):
         * https://arxiv.org/ftp/arxiv/papers/1204/1204.0232.pdf
         */

        /**
         * @todo Or Implement the Math-by-Hand Method (Last Resort):
         * https://silentmatt.com/blog/2011/10/how-bigintegers-work/
         */

        return result;
    }

    BigInteger operator*(const BigInteger& lhs, const BigInteger& rhs) {
        BigInteger result;

        /**
         * @todo Implement the Karatsuba Algorithm:
         * https://brilliant.org/wiki/karatsuba-algorithm/
         */

        //Consider the SS Algorithm: https://tonjanee.home.xs4all.nl/SSAdescription.pdf
        //SSA related: http://www.ams.org/publicoutreach/feature-column/fcarc-multiplication

        return result;
    }

    Rational operator/(const BigInteger& lhs, const BigInteger& rhs) {

        /*************************************************/
        /*************************************************/
        /****FIGURE OUT HOW TO IMPLEMENT THIS FUNCTION****/
        /*************************************************/
        /*************************************************/

    }

    BigInteger operator|(const BigInteger& lhs, const BigInteger& rhs) {
        BigInteger result;

        /**
         * @todo Implement the Newton-Raphson Method
         * https://en.m.wikipedia.org/wiki/Newton%27s_method
         */

        return result;
    }

    BigInteger operator%(const BigInteger& lhs, const BigInteger& rhs) {
        BigInteger result;

        /**
         * @todo Implement the Newton-Raphson Method but with the remainder as the result
         * https://en.m.wikipedia.org/wiki/Newton%27s_method
         */

        return result;
    }

    /**
     * @todo Test the comparison operators
     */

    bool operator==(const BigInteger& lhs, const BigInteger& rhs) {
        return lhs.value == rhs.value;
    }

    bool operator>(const BigInteger& lhs, const BigInteger& rhs) {
        return lhs.value > rhs.value;
    }

    bool operator<(const BigInteger& lhs, const BigInteger& rhs) {
        return lhs.value < rhs.value;
    }

    bool operator>=(const BigInteger& lhs, const BigInteger& rhs) {
        return lhs.value >= rhs.value;
    }

    bool operator<=(const BigInteger& lhs, const BigInteger& rhs) {
        return lhs.value <= rhs.value;
    }

    bool operator!=(const BigInteger& lhs, const BigInteger& rhs) {
        return lhs.value != rhs.value;
    }

    std::string BigInteger::get_str_value() const {
        return this->str_value;
    }

    std::vector<std::uint64_t> BigInteger::get_value() const {
        return this->value;
    }

    bool BigInteger::get_sign() const {
        return this->sign;
    }

} // namespace shaka
