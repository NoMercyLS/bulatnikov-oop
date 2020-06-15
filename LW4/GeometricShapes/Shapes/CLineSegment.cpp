#include "CLineSegment.h"

CLineSegment::CLineSegment(const CPoint& startPoint, const CPoint& endPoint, uint32_t lineColor)
	: m_startPoint(startPoint)
	, m_endPoint(endPoint)
	, m_outlineColor(lineColor)
{
}

double GetDistance(CPoint startPoint, CPoint endPoint)
{
	return sqrt(pow(endPoint.x - startPoint.x, 2) + pow(endPoint.y - startPoint.y, 2));
}


double CLineSegment::GetArea() const
{
	return 0.0;
}
double CLineSegment::GetPerimeter() const
{
	return GetDistance(m_startPoint, m_endPoint);
}

uint32_t CLineSegment::GetOutlineColor() const
{
	return m_outlineColor;
}

CPoint CLineSegment::GetStartPoint() const
{
	return m_startPoint;
}

CPoint CLineSegment::GetEndPoint() const
{
	return m_endPoint;
}

std::string CLineSegment::ToString() const
{
	ostringstream strm;
	strm << "Line segment" << ":" << endl
		 << fixed << setprecision(4)
		 << "\tArea = " << GetArea() << endl
		 << "\tPerimeter = " << GetPerimeter() << endl
		 << "\tOutline color = #" << setfill('0') << setw(6) << hex << GetOutlineColor() << endl
		 << "\tStart point = " << m_startPoint.ToString() << endl
		 << "\tEnd point = " << m_endPoint.ToString() << endl;
	return strm.str();
}