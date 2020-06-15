#include "source.h"
#include "CPoint.h"


CPoint::CPoint(double x, double y)
	: x(x)
	, y(y)
{

}

string CPoint::ToString() const
{
	ostringstream outputStream;
	outputStream << "(" << x << ", " << y << ")";
	return outputStream.str();
}