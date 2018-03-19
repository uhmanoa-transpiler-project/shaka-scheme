//
// Created by Jared Shimabukuro on 2/28/18.
//

#ifndef SHAKA_SCHEME_BIGINTEGER_HPP
#define SHAKA_SCHEME_BIGINTEGER_HPP

#include <string>

namespace shaka {

    /**
     * @brief Imports the representation of Rational to be used by BigInteger
     */
    class Rational;

    /**
     * @brief Imports the representation of Real to be used by BigInteger
     */
    class Real;

    /**
     * @brief Representation of integer values larger than 64-bits
     */
    class BigInteger {
    public:

        /**
         * @brief Default Constructor
         */
        BigInteger();

        /**
         * @brief Copy constructor
         * @param other the BigInteger that is being copied
         */
        BigInteger(const BigInteger& other);

        /**
         * @brief Constructor whose value is initialized to a given string
         * @param val input string
         */
        BigInteger(std::string val);

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

        /**
         * @brief Addition operator for BigIntegers
         * @param lhs The first BigInteger operand
         * @param rhs The second BigInteger operand
         * @return The sum of lhs and rhs
         */
        friend BigInteger operator+(const BigInteger& lhs, const BigInteger& rhs);

        /**
         * @brief Subtraction operator for BigIntegers
         * @param lhs The first BigInteger operand
         * @param rhs The second BigInteger operand
         * @return The difference of lhs and rhs
         */
        friend BigInteger operator-(const BigInteger& lhs, const BigInteger& rhs);

        /**
         * @brief Multiplication operator for BigIntegers
         * @param lhs The first BigInteger operand
         * @param rhs The second BigInteger operand
         * @return The product of lhs and rhs
         */
        friend BigInteger operator*(const BigInteger& lhs, const BigInteger& rhs);

        /**
         * @brief Fraction operator for BigIntegers
         * @param lhs The first BigInteger operand
         * @param rhs The second BigInteger operand
         * @return A Rational value with lhs as the numerator
           and rhs as the denominator
         */
        friend Rational operator/(const BigInteger& lhs, const BigInteger& rhs);

        /**
         * @brief Division operator for BigIntegers
         * @param lhs The first BigInteger operand
         * @param rhs The second BigInteger operand
         * @return The quotient of lhs and rhs
         */
        friend BigInteger operator|(const BigInteger& lhs, const BigInteger& rhs);

        /**
         * @brief Modulo operator for BigIntegers
         * @param lhs The first BigInteger operand
         * @param rhs The second BigInteger operand
         * @return The remainder of the quotient of lhs and rhs
         */
        friend BigInteger operator%(const BigInteger& lhs, const BigInteger& rhs);

        /**
         * @brief Equality operator for BigIntegers
         * @param lhs The first BigInteger operand
         * @param rhs The second BigInteger operand
         * @return Returns 'true' if lhs and rhs are equal
         */
        friend bool operator==(const BigInteger& lhs, const BigInteger& rhs);

        /**
         * @brief Greater-Than operator for BigIntegers
         * @param lhs The first BigInteger operand
         * @param rhs The second BigInteger operand
         * @return Returns 'true' if lhs is greater than rhs
         */
        friend bool operator>(const BigInteger& lhs, const BigInteger& rhs);

        /**
         * @brief Less-Than operator for BigIntegers
         * @param lhs The first BigInteger operand
         * @param rhs The second BigInteger operand
         * @return Returns 'true' if lhs is less than rhs
         */
        friend bool operator<(const BigInteger& lhs, const BigInteger& rhs);

        /**
         * @brief Greater-Than-Or-Equal operator for BigIntegers
         * @param lhs The first BigInteger operand
         * @param rhs The second BigInteger operand
         * @return Returns 'true' if lhs is greater than or equal to rhs
         */
        friend bool operator>=(const BigInteger& lhs, const BigInteger& rhs);

        /**
         * @brief Less-Than-Or-Equal operator for BigIntegers
         * @param lhs The first BigInteger operand
         * @param rhs The second BigInteger operand
         * @return Returns 'true' if lhs is less than or equal to rhs
         */
        friend bool operator<=(const BigInteger& lhs, const BigInteger& rhs);

        /**
         * @brief Inequality operator for BigIntegers
         * @param lhs The first BigInteger operand
         * @param rhs The second BigInteger operand
         * @return Returns 'true' if lhs and rhs are not equal
         */
        friend bool operator!=(const BigInteger& lhs, const BigInteger& rhs);

        std::string get_value() const;

    private:
        std::string value;
    };

} // namespace shaka
#endif //SHAKA_SCHEME_BIGINTEGER_HPP
