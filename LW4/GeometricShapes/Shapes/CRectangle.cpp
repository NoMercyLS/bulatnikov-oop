#include "CRectangle.h"
#include "CPoint.h"

CRectangle::CRectangle(const CPoint& topLeft, double width, double height, uint32_t fillColor, uint32_t outlineColor)
	: m_topLeft(topLeft)
	, m_width(width)
	, m_height(height)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
}

double CRectangle::GetArea() const
{
	return (m_height * m_width);
}

double CRectangle::GetPerimeter() const
{
	return 2 * (m_height + m_width);
}

uint32_t CRectangle::GetFillColor() const
{
	return m_fillColor;
}

uint32_t CRectangle::GetOutlineColor() const
{
	return m_outlineColor;
}

CPoint CRectangle::GetTopLeft() const
{
	return m_topLeft;
}

double CRectangle::GetWidth() const
{
	return m_width;
}

double CRectangle::GetHeight() const
{
	return m_height;
}

string CRectangle::ToString() const
{
	ostringstream strm;
	strm << "Rectangle" << ":" << endl
		 << fixed << setprecision(4)
		 << "\tArea = " << GetArea() << endl
		 << "\tPerimeter = " << GetPerimeter() << endl
		 << "\tOutline color = #" << setfill('0') << setw(6) << hex << m_outlineColor << endl
		 << "\tFill color = #" << setfill('0') << setw(6) << hex << m_fillColor << endl
		 << "\tTop left = " << m_topLeft.ToString() << endl
		 << "\tWidth = " << GetWidth() << endl
		 << "\tHeight = " << GetHeight() << endl;
	return strm.str();
}