#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../Shapes/CCircle.h"
#include "../Shapes/CLineSegment.h"
#include "../Shapes/CPoint.h"
#include "../Shapes/CRectangle.h"
#include "../Shapes/CTriangle.h"
#include "../Shapes/IShape.h"
#include "../Shapes/ISolidShape.h"
#include "../Shapes/Source.h"
#define M_PI 3.14159265358979323846
#define defaultColor 0x808080

SCENARIO("Circle", "[CCircle]")
{
	CPoint circleCenter = CPoint(1.0, 2.0);
	CCircle circle = CCircle(circleCenter, 30.5, defaultColor, defaultColor);

	SECTION("Can get correct center")
	{
		CHECK(circleCenter.x == circle.GetCenter().x);
		CHECK(circleCenter.y == circle.GetCenter().y);
	}

	SECTION("Can get correct radius")
	{
		CHECK(circle.GetRadius() == 30.5);
	}

	SECTION("Can get correct colors")
	{
		CHECK(circle.GetFillColor() == defaultColor);
		CHECK(circle.GetOutlineColor() == defaultColor);
	}

	SECTION("Can get correct perimeter & area")
	{
		CHECK(circle.GetPerimeter() == M_PI*circle.GetRadius()*2);
		CHECK(circle.GetArea() == M_PI*pow(circle.GetRadius(), 2));
	}

	SECTION("Can get correct info")
	{
		ostringstream strm;
		strm << "Circle" << ":" << endl
			<< fixed << setprecision(4)
			<< "\tArea = " << circle.GetArea() << endl
			<< "\tPerimeter = " << circle.GetPerimeter() << endl
			<< "\tOutline color = #" << setfill('0') << setw(6) << hex << circle.GetOutlineColor() << endl
			<< "\tFill color = #" << setfill('0') << setw(6) << hex << circle.GetFillColor() << endl
			<< "\tCenter = " << circle.GetCenter().ToString() << endl
			<< "\tRadius = " << circle.GetRadius() << endl;
		string expected = strm.str();
		CHECK(expected == circle.ToString());
	}
}

SCENARIO("Line", "[CLineSegment]")
{
	CPoint startPoint = CPoint(0.0, 0.0);
	CPoint endPoint = CPoint(12.0, 0.0);
	CLineSegment line = CLineSegment(startPoint, endPoint, defaultColor);

	SECTION("Can get correct start and end points")
	{
		SECTION("Start point")
		{
			CHECK(startPoint.x == line.GetStartPoint().x);
			CHECK(startPoint.y == line.GetStartPoint().y);
		}
		
		SECTION("End point")
		{
			CHECK(endPoint.x == line.GetEndPoint().x);
			CHECK(endPoint.y == line.GetEndPoint().y);
		}
	}

	SECTION("Can get correct area & perimeter")
	{
		CHECK(line.GetArea() == 0);
		CHECK(line.GetPerimeter() == 12.0);
	}

	SECTION("Can get correct color")
	{
		CHECK(line.GetOutlineColor() == defaultColor);
	}

	SECTION("Can get correct info")
	{
		ostringstream strm;
		strm << "Line segment" << ":" << endl
			<< fixed << setprecision(4)
			<< "\tArea = " << line.GetArea() << endl
			<< "\tPerimeter = " << line.GetPerimeter() << endl
			<< "\tOutline color = #" << setfill('0') << setw(6) << hex << line.GetOutlineColor() << endl
			<< "\tStart point = " << line.GetStartPoint().ToString() << endl
			<< "\tEnd point = " << line.GetEndPoint().ToString() << endl;
		string expected = strm.str();
		CHECK(expected == line.ToString());
	}

}

SCENARIO("Point", "[CPoint]")
{
	CPoint somePoint = CPoint(1.1, 2.1);

	SECTION("Can get coordinates")
	{
		CHECK(somePoint.x == 1.1);
		CHECK(somePoint.y == 2.1);
	}

	SECTION("Can get info")
	{
		string expected = "(1.1, 2.1)";
		CHECK(somePoint.ToString() == expected);
	}
}

SCENARIO("Rectangle", "[CRectangle]")
{
	CPoint somePoint = CPoint(1.0, 2.0);
	CRectangle rectangle = CRectangle(somePoint, 20.0, 20.0, defaultColor, defaultColor);

	SECTION("Can get start point")
	{
		CHECK(rectangle.GetTopLeft().x == somePoint.x);
		CHECK(rectangle.GetTopLeft().y == somePoint.y);
	}
	SECTION("Can get height & width")
	{
		CHECK(rectangle.GetWidth() == 20.0);
		CHECK(rectangle.GetHeight() == 20.0);
	}
	SECTION("Can get colors")
	{
		CHECK(rectangle.GetOutlineColor() == defaultColor);
		CHECK(rectangle.GetFillColor() == defaultColor);
	}
	SECTION("Can get area & perimeter")
	{
		CHECK(rectangle.GetArea() == 400.0);
		CHECK(rectangle.GetPerimeter() == 80.0);
	}
	SECTION("Can get info")
	{
		ostringstream strm;
		strm << "Rectangle" << ":" << endl
			<< fixed << setprecision(4)
			<< "\tArea = " << rectangle.GetArea() << endl
			<< "\tPerimeter = " << rectangle.GetPerimeter() << endl
			<< "\tOutline color = #" << setfill('0') << setw(6) << hex << rectangle.GetOutlineColor() << endl
			<< "\tFill color = #" << setfill('0') << setw(6) << hex << rectangle.GetFillColor ()<< endl
			<< "\tTop left = " << rectangle.GetTopLeft().ToString() << endl
			<< "\tWidth = " << rectangle.GetWidth() << endl
			<< "\tHeight = " << rectangle.GetHeight() << endl;
		string expected = strm.str();
	}
}

SCENARIO("Triangle", "[CTriangle]")
{
	CPoint vert1 = CPoint(5, 0);
	CPoint vert2 = CPoint(5, 4);
	CPoint vert3 = CPoint(0, 0);
	CTriangle triangle = CTriangle(vert1, vert2, vert3, defaultColor, defaultColor);

	SECTION("Can get correct vertexes")
	{
		SECTION("Vertex #1")
		{
			CHECK(triangle.GetVertex1().x == 5);
			CHECK(triangle.GetVertex1().y == 0);
		}
		SECTION("Vertex #2")
		{
			CHECK(triangle.GetVertex2().x == 5);
			CHECK(triangle.GetVertex2().y == 4);
		}
		SECTION("Vertex #3")
		{
			CHECK(triangle.GetVertex3().x == 0);
			CHECK(triangle.GetVertex3().y == 0);
		}
	}
	SECTION("Can get correct colors")
	{
		CHECK(triangle.GetFillColor() == defaultColor);
		CHECK(triangle.GetOutlineColor() == defaultColor);
	}
	SECTION("Can get correct area & perimeter")
	{
		CHECK(triangle.GetPerimeter() == 6.4031242374328487 + 5 + 4);
		CHECK(triangle.GetArea() == 10);
	}
	SECTION("Can get correct info")
	{
		ostringstream strm;
		strm << "Triangle" << ":" << endl
			<< fixed << setprecision(4)
			<< "\tArea = " << triangle.GetArea() << endl
			<< "\tPerimeter = " << triangle.GetPerimeter() << endl
			<< "\tOutline color = #" << setfill('0') << setw(6) << hex << triangle.GetOutlineColor() << endl
			<< "\tFill color = #" << setfill('0') << setw(6) << hex << triangle.GetFillColor() << endl
			<< "\tVertex1 = " << triangle.GetVertex1().ToString() << endl
			<< "\tVertex2 = " << triangle.GetVertex2().ToString() << endl
			<< "\tVertex3 = " << triangle.GetVertex3().ToString() << endl;
		CHECK(strm.str() == triangle.ToString());
	}
}