#include "CTriangle.h"
#include "CLineSegment.h"

CTriangle::CTriangle(const CPoint& vertex1, const CPoint& vertex2, const CPoint& vertex3, uint32_t fillColor, uint32_t outlineColor)
	: m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
}

double CTriangle::GetArea() const
{
	double side1 = GetDistance(m_vertex1, m_vertex2);
	double side2 = GetDistance(m_vertex2, m_vertex3);
	double side3 = GetDistance(m_vertex1, m_vertex3);
	double halfPerimeter = (side1 + side2 + side3) / 2;
	return sqrt(halfPerimeter * (halfPerimeter - side1) * (halfPerimeter - side2) * (halfPerimeter - side3));;
}

double CTriangle::GetPerimeter() const
{
	return GetDistance(m_vertex1, m_vertex2) + GetDistance(m_vertex2, m_vertex3) + GetDistance(m_vertex3, m_vertex1);
}


CPoint CTriangle::GetVertex1() const
{
	return m_vertex1;
}

CPoint CTriangle::GetVertex2() const
{
	return m_vertex2;
}

CPoint CTriangle::GetVertex3() const
{
	return m_vertex3;
}

uint32_t CTriangle::GetFillColor() const
{
	return m_fillColor;
}

uint32_t CTriangle::GetOutlineColor() const
{
	return m_outlineColor;
}

std::string CTriangle::ToString() const
{
	ostringstream strm;
	strm << "Triangle" << ":" << endl
		 << fixed << setprecision(4)
		 << "\tArea = " << GetArea() << endl
		 << "\tPerimeter = " << GetPerimeter() << endl
		 << "\tOutline color = #" << setfill('0') << setw(6) << hex << m_outlineColor << endl
		 << "\tFill color = #" << setfill('0') << setw(6) << hex << m_fillColor << endl
		 << "\tVertex1 = " << m_vertex1.ToString() << endl
		 << "\tVertex2 = " << m_vertex2.ToString() << endl
		 << "\tVertex3 = " << m_vertex3.ToString() << endl;
	return strm.str();
}