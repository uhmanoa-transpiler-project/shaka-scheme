//
// Created by Jared Shimabukuro on 3/3/18.
//

#include "shaka_scheme/system/base/BigInteger.hpp"
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
        std::string LOperand = lhs.get_str_value();
        std:: string ROperand = rhs.get_str_value();
        std::string product = schonhageStrassen(LOperand, ROperand, LOperand.length()+1, ROperand.length()+1);

        BigInteger result(product);
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

    // Credit to Sanfoundry for the C++ implementation of the Schonhage-Strassen Algorithm
    // https://www.sanfoundry.com/cpp-program-implement-schonhage-strassen-algorithm-multiplication-two-numbers/
    std::string schonhageStrassen(std::string x, std::string y, int n, int m)
    {
        bool signX = false, signY = false;
        int linearConvolution[n + m - 1];

        for (int i = 0; i < (n + m - 1); i++) {
            linearConvolution[i] = 0;
        }
        if (x[0] == '-') {
            signX = true;
            x.erase(0,1);
            n--;
        }

        if (y[0] == '-') {
            signY = true;
            y.erase(0,1);
            m--;
        }
        int xNum = n - 2;
        int yNum = m - 2;

        for (int i = 0; i < m - 1; i++)
        {
            for (int j = 0; j < n - 1; j++)
            {
                linearConvolution[i + j] += (std::stoi(y.substr(yNum - i,1)) * std::stoi(x.substr(xNum - j,1)));
            }
        }

        std::int64_t nextCarry = 0;
        std::string bigProduct = "";

        for (int i = 0; i < n + m - 1; i++)
        {
            linearConvolution[i] += nextCarry;
            if(i < n + m - 2)
                bigProduct.insert(0, std::to_string((linearConvolution[i] % 10)));
            nextCarry = linearConvolution[i] / 10;
        }

        if (signX && signY || !signX && !signY)
            return bigProduct;

        else {
            bigProduct.insert(0,"-");
            return bigProduct;
        }
    }

} // namespace shaka
