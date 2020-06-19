#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../RationalNumber/CONSTANT.h"
#include "../RationalNumber/CRational.h"
void VerifyRational(const CRational& rational, int expectedNum, int excpectedDen)
{
	CHECK(rational.GetDenominator() == excpectedDen);
	CHECK(rational.GetNumerator() == expectedNum);
}

TEST_CASE("The greatest common divisor is determined correctly", "[gcd]")
{
	REQUIRE(GCD(0, 0) == 1u);
	REQUIRE(GCD(2, 3) == 1u);
	REQUIRE(GCD(4, 8) == 4u);
	REQUIRE(GCD(128, 256) == 128u);
	REQUIRE(GCD(8, 132) == 4u);
}

TEST_CASE("Check all methods")
{
	SECTION("Default values")
	{
		VerifyRational(CRational(), 0, 1);
	}

	SECTION("Successful construction")
	{
		VerifyRational(CRational(2, 5), 2, 5);
		VerifyRational(CRational(2, -5), -2, 5);
		VerifyRational(CRational(-2, -3), 2, 3);
		VerifyRational(CRational(0, 1), 0, 1);
	}

	SECTION("Successfull normalize after construction")
	{
		VerifyRational(CRational(3, 9), 1, 3);
		VerifyRational(CRational(2, 4), 1, 2);
		VerifyRational(CRational(14, 49), 2, 7);
		VerifyRational(CRational(22, 88), 1, 4);
		VerifyRational(CRational(3, 6), 1, 2);
	}

	SECTION("Zero denominator")
	{
		CHECK_THROWS_AS(CRational(1, 0), invalid_argument);
	}

	SECTION("Double convertion")
	{
		CHECK(CRational(21, 10).ToDouble() == Approx(2.1));
		CHECK(CRational(212121, 1000000).ToDouble() == Approx(0.212121));
		CHECK(CRational(13, 26).ToDouble() == Approx(0.5));
		CHECK(CRational(13, 260).ToDouble() == Approx(0.05));
		CHECK(CRational(1, 1).ToDouble() == Approx(1.0));
	}

	SECTION("Compound fraction")
	{
		SECTION("Contains int part")
		{
			CHECK(CRational(10, 4).ToCompoundFraction().first == 2);
			CHECK(CRational(10, 4).ToCompoundFraction().second == CRational(1, 2));
		}
		
		SECTION("No int part")
		{
			CHECK(CRational(2, 4).ToCompoundFraction().first == 0);
			CHECK(CRational(2, 4).ToCompoundFraction().second == CRational(1, 2));
		}

		SECTION("Negative int part")
		{
			CHECK(CRational(-10, 4).ToCompoundFraction().first == -2);
			CHECK(CRational(-10, 4).ToCompoundFraction().second == CRational(-1, 2));
		}
	}
}

TEST_CASE("Operators testing", "[operator]")
{
	SECTION("Binary plus")
	{
		SECTION("Two positive rationals")
		{
			CRational res = CRational(1, 2) + CRational(1, 4);
			VerifyRational(res, 3, 4);
		}
		SECTION("Two negative rationals")
		{
			CRational res = CRational(-1, 2) + CRational(-1, 4);
			VerifyRational(res, -3, 4);
		}
		SECTION("One negative one positive")
		{
			CRational res = CRational(-1, 2) + CRational(1, 4);
			VerifyRational(res, -1, 4);
		}
		SECTION("Two integers")
		{
			SECTION("Positive integers")
			{
				int n1 = 1;
				int n2 = 2;
				CRational res = n1 + n2;
				VerifyRational(res, 3, 1);
			}
			SECTION("Negative integers")
			{
				int n1 = -1;
				int n2 = -2;
				CRational res = n1 + n2;
				VerifyRational(res, -3, 1);
			}
			SECTION("One negative one positive integers")
			{
				int n1 = 1;
				int n2 = -2;
				CRational res = n1 + n2;
				VerifyRational(res, -1, 1);
			}
		}
		SECTION("One integer one rational")
		{
			SECTION("Positive int")
			{
				int n1 = 1;
				CRational res = n1 + CRational(1, 2);
				VerifyRational(res, 3, 2);
			}
			SECTION("Negative int")
			{
				int n1 = -1;
				CRational res = n1 + CRational(1, 2);
				VerifyRational(res, -1, 2);
			}
			SECTION("Negative rational")
			{
				int n1 = 1;
				CRational res = n1 + CRational(-1, 2);
				VerifyRational(res, 1, 2);
			}
		}
	}
	SECTION("Binary minus")
	{
		SECTION("Two positive rationals")
		{
			CRational n1(1, 2);
			CRational n2(1, 6);
			CRational res = n1 - n2;
			VerifyRational(res, 1, 3);
		}
		SECTION("Two negative rationals")
		{
			CRational n1(-1, 2);
			CRational n2(-1, 6);
			CRational res = n1 - n2;
			VerifyRational(res, -1, 3);
		}
		SECTION("One integer one rational")
		{
			CRational n1(1, 2);
			int n2 = 1;
			CRational res = n1 - n2;
			VerifyRational(res, -1, 2);
		}
		SECTION("Two integers")
		{
			int n1 = 1;
			int n2 = 2;
			CRational res = n1 - n2;
			VerifyRational(res, -1, 1);
		}
	}
	SECTION("Increment")
	{
		SECTION("Two rationals")
		{
			CRational n1(1, 2);
			CRational n2(1, 6);
			n1 += n2;
			VerifyRational(n1, 2, 3);
		}
		SECTION("One rational one integer")
		{
			CRational n1(1, 2);
			int n2 = 1;
			n1 += n2;
			VerifyRational(n1, 3, 2);
		}
	}
	SECTION("Decrement")
	{
		SECTION("Two rationals")
		{
			CRational n1(1, 2);
			CRational n2(1, 6);
			n1 -= n2;
			VerifyRational(n1, 1, 3);
		}
		SECTION("One rational one integer")
		{
			CRational n1(1, 2);
			int n2 = 1;
			n1 -= n2;
			VerifyRational(n1, -1, 2);
		}
	}
	SECTION("Multiply")
	{
		SECTION("Two positive rationals")
		{
			CRational n1(1, 2);
			CRational n2(2, 3);
			CRational res = n1 * n2;
			VerifyRational(res, 1, 3);
		}
		SECTION("Two negative rationals")
		{
			CRational n1(-1, 2);
			CRational n2(-1, 6);
			CRational res = n1 * n2;
			VerifyRational(res, 1, 12);
		}
		SECTION("Rational & int")
		{
			CRational n1(1, 2);
			int n2 = -3;
			CRational res = n1 * n2;
			VerifyRational(res, -3, 2);
		}
	}
	SECTION("Division")
	{
		SECTION("Two positive rationals")
		{
			CRational n1(1, 2);
			CRational n2(2, 3);
			CRational res = n1 / n2;
			VerifyRational(res, 3, 4);
		}
		SECTION("Two negative rationals")
		{
			CRational n1(-1, 2);
			CRational n2(-1, 6);
			CRational res = n1 / n2;
			VerifyRational(res, 3, 1);
		}
		SECTION("Rational and integer")
		{
			CRational n1(1, 2);
			int n2 = 5;
			CRational res = n1 / n2;
			VerifyRational(res, 1, 10);
		}
	}
	SECTION("Multiply increment")
	{
		SECTION("Two rationals")
		{
			CRational n1(1, 2);
			CRational n2(2, 3);
			n1 *= n2;
			VerifyRational(n1, 1, 3);
		}
		SECTION("One int one rational")
		{
			CRational n1(1, 2);
			int n2 = 3;
			n1 *= n2;
			VerifyRational(n1, 3, 2);
		}
	}
	SECTION("Division decrement")
	{
		SECTION("Two rationals")
		{
			CRational n1(1, 2);
			CRational n2(2, 3);
			n1 /= n2;
			VerifyRational(n1, 3, 4);
		}
		SECTION("One int one rational")
		{
			CRational n1(1, 2);
			int n2 = 3;
			n1 /= n2;
			VerifyRational(n1, 1, 6);
		}
	}
	SECTION("Comparsion")
	{
		CHECK(CRational(3, 6) == CRational(1, 2));
		CHECK(CRational(6, 3) == 2);
		CHECK(CRational(1, 2) != 2);
	}
	SECTION("Greater & less")
	{
		CHECK(CRational(1, 2) > CRational(1, 4));
		CHECK(CRational(1, 3) > CRational(1, 4));
		CHECK(CRational(1, 5) < CRational(1, 4));
		CHECK(CRational(-1, 2) < CRational(1, 4));
		CHECK(CRational(-1, 2) > CRational(-3, 4));
	}
	SECTION("Greater or equal & less or equal")
	{
		CHECK(CRational(3, 1) >= 3);
		CHECK(CRational(1, 2) <= 3);
		CHECK(CRational(3, 1) <= 3);
		CHECK(!(CRational(1, 3) >= 3));
		CHECK(!(CRational(4, 1) <= 3));
		CHECK(CRational(3, 1) <= CRational(14, 3));
		CHECK(!(CRational(1, 3) >= 3));
		CHECK(!(CRational(4, 1) <= CRational(3,2)));
	}
	SECTION("Output stream")
	{
		SECTION("Positive")
		{
			CRational num(5, 6);
			stringstream output;
			output << num;
			CHECK(output.str() == "5/6");
		}
		SECTION("Negative")
		{
			CRational num(-5, 6);
			stringstream output;
			output << num;
			CHECK(output.str() == "-5/6");
		}
	}
	SECTION("Input stream")
	{
		SECTION("Input positive")
		{
			CRational num;
			stringstream input("5/6");
			input >> num;
			VerifyRational(num, 5, 6);
		}
		SECTION("Input negative")
		{
			CRational num;
			stringstream input("-5/6");
			input >> num;
			VerifyRational(num, -5, 6);
		}
		SECTION("Input 2 negatives")
		{
			CRational num;
			stringstream input("-5/-6");
			input >> num;
			VerifyRational(num, 5, 6);
		}
		SECTION("Incorrect")
		{

			CRational num;
			stringstream input("FAILED:)");
			input >> num;
			CHECK(input.fail());
		}
	}
}