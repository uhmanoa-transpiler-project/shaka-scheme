#ifndef BIGINT_H
#define BIGINT_H
#include <cmath>
#include <boost/variant.hpp>
#include <typeinfo>
#include <vector>
#include <string>

class BigInt
{
    public:

    ~BigInt() {}

    // Description of Constructors below:
    //  store value in vector<int> given a long long int
    //  store value in vector<int> given a string

    BigInt(long long int llival) { llint_to_array(llival); }
    BigInt(std::string sval) { string_to_intarray(sval); }

    // Operations to be overloaded:
    void operator=(BigInt b);
    void operator=(std::vector<int> v);
    //      Add  --- Ky
    //      Subtract  --- Ky
    //      Multiply
    BigInt operator*(BigInt b);
    //      Exponents
    //      Factorial
    //      Divide
    //      Modulo

    // Helper Fucntions
    void insert_beginning(int num);
    int get_size(void);
    int get_value(int index);
    void print_value(void);

private:

    std::vector<int> value;

    // Functions for constructors
    void llint_to_array(long long int v);
    void string_to_intarray(std::string s);

};

/*-------------------------------- MEMBER FUNCTION IMPLEMENTATION -----------*/

void BigInt::insert_beginning(int num)
{
   value.insert(value.begin(), num);
}

void BigInt::operator=(BigInt b)
{
  for(int i = 0; i < b.get_size(); i++)
  { value.push_back(b.get_value(i)); }
}

/*
BigInt BigInt::operator*(BigInt b)
{
  BigInt temp(0);

  for(int i = (this->get_size()-1); i >= 0; i--)
  { temp.insert_beginning(this->get_value(i)); }

  temp.print_value();
  printf("\n");

  int Ans, A, B, C, prevA, prevB, prevC;

  // Setup for Multiplication
  for(;temp.get_size() > b.get_size();)  // make the two the same # of digits for easier computation
    { b.insert_beginning(0); }
  for(;temp.get_size() < b.get_size();)  // can change if algorithm is too slow
    { temp.insert_beginning(0); }
  if(temp.get_size()%2)                // if it's an odd amount of digits
    {
      b.insert_beginning(0);
      temp.insert_beginning(0);
    }

  A = B = C = prevA = prevB = prevC = 1;
  int middle = temp.get_size()/2;
  printf("middle = %d\n", middle);

  Ans = 0;

  for(int index = 0; index <= middle; index = index+2)
  {
    A = A * temp.get_value(index)*b.get_value(index);
    B = B * temp.get_value(index+1)*b.get_value(index+1);
    C = C * (temp.get_value(index)+temp.get_value(index+1))*(b.get_value(index)+b.get_value(index+1)) - A - B;

    Ans = Ans + (A*100 + C*10 + B);

    printf("A = %d\n", A);
    printf("B = %d\n", B);
    printf("C = %d\n", C);
    printf("Ans = %d\n", Ans);
  }

  return temp;
}
*/

BigInt BigInt::operator*(BigInt b)
{
  BigInt temp(0);

  for(int i = (this->get_size()-1); i >= 0; i--)
  { temp.insert_beginning(this->get_value(i)); }

  temp.print_value();
  printf("\n");

  int Ans, A, B, C, prevAns, prevA, prevB, prevC;

  // Setup for Multiplication
  for(;temp.get_size() > b.get_size();)  // make the two the same # of digits for easier computation
    { b.insert_beginning(0); }
  for(;temp.get_size() < b.get_size();)  // can change if algorithm is too slow
    { temp.insert_beginning(0); }
  if(temp.get_size()%2)                // if it's an odd amount of digits
    {
      b.insert_beginning(0);
      temp.insert_beginning(0);
    }

  A = B = C = prevA = prevB = prevC = 1;
  int middle = temp.get_size()/2;
  printf("middle = %d\n", middle);

  Ans = prevAns = 0;

  for(int index = 0; index <= middle; index = index+2)
  {

    A = prevA * temp.get_value(index)*b.get_value(index);
    B = prevB * temp.get_value(index+1)*b.get_value(index+1);
    C = (temp.get_value(index)+temp.get_value(index+1))*(b.get_value(index)+b.get_value(index+1)) - A - B;

    Ans = Ans + (A*100 + C*10 + B);

    prevA = A;
    prevB = B;
    prevC = C;
    prevAns = Ans;

    printf("A = %d\n", A);
    printf("B = %d\n", B);
    printf("C = %d\n", C);
    printf("Ans = %d\n", Ans);

  }

  return temp;
}



int BigInt::get_value(int index)
{ return value[index]; }

int BigInt::get_size(void)
{ return value.size(); }

void BigInt::print_value(void)
{
  for(unsigned long int i = 0; i < value.size(); i++)
  { std::cout << value[i]; }
}

// Private Functions for Constructors
void BigInt::llint_to_array(long long int v)
{
  for(int llv = v; llv > 0; llv = llv/10)
  { value.insert(value.begin(), llv%10); }
}

void BigInt::string_to_intarray(std::string s)
{
}



#endif // BIGINT_H
