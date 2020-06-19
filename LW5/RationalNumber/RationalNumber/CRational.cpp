#include "CRational.h"
#include "CONSTANT.h"

using namespace std;

CRational::CRational(int numerator, int denominator)
	: m_numerator(numerator)
	, m_denominator(denominator)
{
	if (denominator == 0)
	{
		throw invalid_argument(InvalidDenominator);
	}
	if (denominator < 0)
	{
		m_numerator *= -1;
		m_denominator *= -1;
	}
	Normalize();
}

int CRational::GetNumerator() const
{
	return m_numerator;
}

int CRational::GetDenominator() const
{
	return m_denominator;
}

double CRational::ToDouble() const
{
	return double(m_numerator) / double(m_denominator);
}

unsigned GCD(unsigned a, unsigned b)
{
	while (b != 0)
	{
		swap(a, b);
		b %= a;
	}
	return (a != 0) ? a : 1;
}

void CRational::Normalize()
{
	const int gcd = GCD(abs(m_numerator), m_denominator);
	m_numerator /= gcd;
	m_denominator /= gcd;
}

pair<int, CRational> CRational::ToCompoundFraction() const
{
	int integerPart = m_numerator / m_denominator;
	int numerator = m_numerator - integerPart * m_denominator;
	return pair<int, CRational>(integerPart, CRational(numerator, m_denominator));
}

CRational& CRational::operator+=(CRational const& rational)
{
	*this = *this + rational;
	return *this;
}

CRational& CRational::operator-=(CRational const& rational)
{
	*this = *this - rational;
	return *this;
}

CRational& CRational::operator*=(CRational const& rational)
{
	*this = *this * rational;
	return *this;
}

CRational& CRational::operator/=(CRational const& rational)
{
	*this = *this / rational;
	return *this;
}

CRational const CRational::operator+() const
{
	return *this;
}

CRational const CRational::operator-() const
{
	return CRational(-m_numerator, m_denominator);
}

CRational const operator+(CRational const& rational1, CRational const& rational2)
{
	return CRational(rational1.GetNumerator() * rational2.GetDenominator() + rational2.GetNumerator() * rational1.GetDenominator(),
		rational1.GetDenominator() * rational2.GetDenominator());
}

CRational const operator-(CRational const& rational1, CRational const& rational2)
{
	return rational1 + -rational2;
}

CRational const operator*(CRational const& rational1, CRational const& rational2)
{
	return CRational(rational1.GetNumerator() * rational2.GetNumerator(), rational1.GetDenominator() * rational2.GetDenominator());
}

CRational const operator/(CRational const& rational1, CRational const& rational2)
{
	return CRational(rational1.GetNumerator() * rational2.GetDenominator(), rational1.GetDenominator() * rational2.GetNumerator());
}

bool const operator==(CRational const& rational1, CRational const& rational2)
{
	return rational1.GetNumerator() == rational2.GetNumerator() && rational1.GetDenominator() == rational2.GetDenominator();
}

bool const operator!=(CRational const& rational1, CRational const& rational2)
{
	return !(rational1 == rational2);
}

bool const operator<(CRational const& rational1, CRational const& rational2)
{
	return rational1.GetNumerator() * rational2.GetDenominator() < rational2.GetNumerator() * rational1.GetDenominator();
}

bool const operator>(CRational const& rational1, CRational const& rational2)
{
	return rational1.GetNumerator() * rational2.GetDenominator() > rational2.GetNumerator()* rational1.GetDenominator();
}

bool const operator<=(CRational const& rational1, CRational const& rational2)
{
	return !(rational1 > rational2);
}

bool const operator>=(CRational const& rational1, CRational const& rational2)
{
	return !(rational1 < rational2);
}

ostream& operator<<(std::ostream& stream, CRational const& rational)
{
	stream << rational.GetNumerator() << '/' << rational.GetDenominator();
	return stream;
}

istream& operator>>(std::istream& stream, CRational& rational)
{
	int numerator = 0;
	int denominator = 1;
	if (stream >> numerator && stream.get() == '/' && stream >> denominator)
	{
		rational = CRational(numerator, denominator);
	}
	return stream;
}