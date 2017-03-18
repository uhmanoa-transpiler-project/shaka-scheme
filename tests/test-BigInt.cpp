#include "gtest/gtest.h"
#include "BigInt.h"

/*
TEST(BigInt, constructor_lli)
{
   BigInt a(12345789);
}
*/

int main(int argc, char* argv[])
{
  /*
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
  */

  BigInt a(1234);
  // a.print_value();

  BigInt b(4321);
  // b.print_value();

  BigInt c = b;
  c = b*a;
  // c.print_value();
}
