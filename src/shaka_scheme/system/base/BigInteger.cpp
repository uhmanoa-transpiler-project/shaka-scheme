//
// Created by Jared Shimabukuro on 3/3/18.
//

#include "shaka_scheme/system/base/BigInteger.hpp"
#include "shaka_scheme/system/base/Rational.hpp"
#include "shaka_scheme/system/base/Real.hpp"

namespace shaka {
    BigInteger::operator Rational() {
        Rational result;
        /*************************************************/
        /*************************************************/
        /*** FIGURE OUT HOW TO IMPLEMENT THIS FUNCTION ***/
        /*************************************************/
        /*************************************************/
        return result;
    }

    /**
     * @todo Test the conversion from BigInteger to Real
     */
    BigInteger::operator Real() {
        Real result((double) value);
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

} // namespace shaka