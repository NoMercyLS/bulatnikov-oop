#pragma once
#include "ISolidShape.h"
#include "CPoint.h"
#include "Source.h"

class CCircle : public ISolidShape
{
public:
	CCircle(const CPoint& center, double radius, uint32_t fillColor, uint32_t outlineColor);

	double GetArea() const override;
	double GetPerimeter() const override;
	uint32_t GetFillColor() const override;
	uint32_t GetOutlineColor() const override;

	std::string ToString() const override;

	CPoint GetCenter() const;
	double GetRadius() const;
private:
	CPoint m_center;
	double m_radius;

	uint32_t m_outlineColor;
	uint32_t m_fillColor;
};

