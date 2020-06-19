#pragma once
#include <sstream>
using namespace std;
class CRational
{
public:
	CRational(int numerator = 0, int denominator = 1);

	int GetNumerator() const;
	int GetDenominator() const;

	double ToDouble() const;

	pair<int, CRational> ToCompoundFraction()const;

	CRational const operator+() const;
	CRational const operator-() const;

	CRational& operator +=(CRational const& rational);
	CRational& operator -=(CRational const& rational);
	CRational& operator *=(CRational const& rational);
	CRational& operator /=(CRational const& rational);
private:
	int m_numerator;
	int m_denominator;

	void Normalize();
};

CRational const operator+(CRational const& rational1, CRational const& rational2);
CRational const operator-(CRational const& rational1, CRational const& rational2);
CRational const operator*(CRational const& rational1, CRational const& rational2);
CRational const operator/(CRational const& rational1, CRational const& rational2);

bool const operator ==(CRational const& rational1, CRational const& rational2);
bool const operator !=(CRational const& rational1, CRational const& rational2);
bool const operator < (CRational const& rational1, CRational const& rational2);
bool const operator > (CRational const& rational1, CRational const& rational2);
bool const operator <= (CRational const& rational1, CRational const& rational2);
bool const operator >= (CRational const& rational1, CRational const& rational2);

ostream& operator <<(std::ostream& stream, CRational const& rational);
istream& operator >>(std::istream& stream, CRational& rational);

unsigned GCD(unsigned a, unsigned b);