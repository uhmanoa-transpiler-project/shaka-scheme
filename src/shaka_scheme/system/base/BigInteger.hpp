//
// Created by Jared Shimabukuro on 2/28/18.
//

#ifndef SHAKA_SCHEME_BIGINTEGER_HPP
#define SHAKA_SCHEME_BIGINTEGER_HPP

namespace shaka {

    class Rational;
    class Real;

    class BigInteger {
    public:

        BigInteger(const BigInteger& other) :
                value(other.value) {};
        BigInteger(std::string val) :
                value(val) {};

        /**
         * @brief Implicit type conversion operator for BigInteger -> Rational
         * Needed for interop between numeric subtypes in operator overloads
         * @return The Rational conversion for this BigInteger object
         */
        operator Rational();
        /**
         * @brief Implicit type conversion operator for BigInteger -> Real
         * Needed for interop between numeric subtypes in operator overloads
         * @return The Real conversion for this BigInteger object
         */
        operator Real();

        // arithmetic operators for BigIntegers
        friend BigInteger operator+(const BigInteger& lhs, const BigInteger& rhs);
        friend BigInteger operator-(const BigInteger& lhs, const BigInteger& rhs);
        friend BigInteger operator*(const BigInteger& lhs, const BigInteger& rhs);
        friend Rational operator/(const BigInteger& lhs, const BigInteger& rhs);
        friend BigInteger operator|(const BigInteger& lhs, const BigInteger& rhs);
        friend BigInteger operator%(const BigInteger& lhs, const BigInteger& rhs);

        // comparison operators for BigIntegers
        friend bool operator==(const BigInteger& lhs, const BigInteger& rhs);
        friend bool operator>(const BigInteger& lhs, const BigInteger& rhs);
        friend bool operator<(const BigInteger& lhs, const BigInteger& rhs);
        friend bool operator>=(const BigInteger& lhs, const BigInteger& rhs);
        friend bool operator<=(const BigInteger& lhs, const BigInteger& rhs);
        friend bool operator!=(const BigInteger& lhs, const BigInteger& rhs);

        std::string get_value() const {
            return this->value;
        }

    private:
        std::string value;
    };

} // namespace shaka
#endif //SHAKA_SCHEME_BIGINTEGER_HPP
