#pragma once
#include "Source.h"

class CPoint
{
public:
	CPoint(double x, double y);

	double x = 0;
	double y = 0;
	
	string ToString() const;
};

