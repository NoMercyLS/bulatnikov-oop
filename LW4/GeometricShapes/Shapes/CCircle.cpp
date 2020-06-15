#include "CCircle.h"

#define M_PI 3.14159265358979323846

CCircle::CCircle(const CPoint& center, double radius, uint32_t fillColor, uint32_t outlineColor)
	: m_center(center)
	, m_radius(radius)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
}

double CCircle::GetArea() const
{
	return (M_PI * pow(m_radius, 2));
}

double CCircle::GetPerimeter() const
{
	return (2 * M_PI * m_radius);
}

CPoint CCircle::GetCenter() const
{
	return m_center;
}

double CCircle::GetRadius() const
{
	return m_radius;
}

uint32_t CCircle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t CCircle::GetFillColor() const
{
	return m_fillColor;
}

string CCircle::ToString() const
{
	ostringstream strm;
	strm << "Circle" << ":" << endl
		 << fixed << setprecision(4)
		 << "\tArea = " << GetArea() << endl
		 << "\tPerimeter = " << GetPerimeter() << endl
		 << "\tOutline color = #" << setfill('0') << setw(6) << hex << m_outlineColor << endl
		 << "\tFill color = #" << setfill('0') << setw(6) << hex << m_fillColor << endl
		 << "\tCenter = " << m_center.ToString() << endl
		 << "\tRadius = " << GetRadius() << endl;
	return strm.str();
}