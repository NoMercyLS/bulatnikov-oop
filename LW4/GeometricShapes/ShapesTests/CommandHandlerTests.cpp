#include "../Shapes/Source.h"
#include "../Shapes/CCommandHandler.h"
#include "../../../catch2/catch.hpp"
void CommandHandlerVerifier(const string& command, const string& expected)
{
	stringstream input;
	stringstream output;
	CCommandHandler handler = CCommandHandler(input, output);
	input << command;
	CHECK(handler.HandleCommand());
	CHECK(input.eof());
	handler.Info();
	CHECK(output.str() == expected);
}

SCENARIO("Add different shapes")
{
	SECTION("Triangle")
	{
		SECTION("Correct triangle")
		{
			string expected = R"(All shapes:
Triangle:
	Area = 6.0000
	Perimeter = 13.3006
	Outline color = #000000
	Fill color = #ffffff
	Vertex1 = (-2, 3)
	Vertex2 = (4, 3)
	Vertex3 = (2, 5)

)";
			CommandHandlerVerifier("Triangle -2 3 4 3 2 5 000000 ffffff", expected);
		}
		SECTION("Uncorrect triangle")
		{
			string expected = R"(Failed to create a triangle.
Usage: Triangle <x1> <y1> <x2> <y2> <x3> <y3>( <outline color> <fill color> )
)";
			CommandHandlerVerifier("Triangle 222 222 -2 3 4 3 2 5 000000 ffffff", expected);
		}
	}
	SECTION("Rectangle")
	{
		SECTION("Correct rectangle")
		{
			string expected = R"(All shapes:
Rectangle:
	Area = 1200.0000
	Perimeter = 160.0000
	Outline color = #000000
	Fill color = #ffffff
	Top left = (200, 100)
	Width = 60.0000
	Height = 20.0000

)";
			CommandHandlerVerifier("Rectangle 200 100 60 20 000000 ffffff", expected);
		}
		SECTION("Uncorrect rectangle")
		{
			string expected = R"(Failed to create a rectangle.
Usage: Rectangle <x> <y> <width> <height> ( <outline color> <fill color> )
)";
			CommandHandlerVerifier("Rectangle 200 100 60 20 51 000000 ffffff", expected);
		}
	}
	SECTION("Line segment")
	{
		SECTION("Correct line segment")
		{
			string expected = R"(All shapes:
Line segment:
	Area = 0.0000
	Perimeter = 20.3760
	Outline color = #808080
	Start point = (5.25, 10.75)
	End point = (25.1, 15.35)

)";
			CommandHandlerVerifier("LineSegment 5.25 10.75 25.1 15.35 808080", expected);
		}
		SECTION("Uncorrect line segment")
		{
			string expected = R"(Failed to create a line segment.
Usage: LineSegment <x1> <y1> <x2> <y2> ( <outline color> )
)";
			CommandHandlerVerifier("LineSegment 5.25 10.75 25.1 15.35 15.12 808080", expected);
		}
	}
	SECTION("Circle")
	{
		SECTION("Correct circle")
		{
			string expected = R"(All shapes:
Circle:
	Area = 5026.5482
	Perimeter = 251.3274
	Outline color = #000000
	Fill color = #ffffff
	Center = (10, 9)
	Radius = 40.0000

)";
			CommandHandlerVerifier("Circle 10 9 40 000000 ffffff", expected);
		}
		SECTION("Uncorrect circle")
		{
			string expected = R"(Failed to create a circle.
Usage: Circle <x> <y> <radius> ( <outline color> <fill color> )
)";
			CommandHandlerVerifier("Circle 10 9 40 20 000000 ffffff", expected);
		}
	}
}

SCENARIO("Unknown command")
{
	stringstream input, output;
	input << "Hello world!";
	CCommandHandler handler = CCommandHandler(input, output);
	CHECK(!handler.HandleCommand());
}

SCENARIO("Max area shape")
{
	stringstream input, output;
	CCommandHandler handler = CCommandHandler(input, output);
	input << "Circle 10 9 40 000000 ffffff" << '\n'
		<< "Rectangle 200 100 60 20 000000 ffffff";
	while (!input.eof())
	{
		handler.HandleCommand();
	}
	handler.GetShapeWithMaxArea();
	string expected = R"(Shape with max area is Circle:
	Area = 5026.5482
	Perimeter = 251.3274
	Outline color = #000000
	Fill color = #ffffff
	Center = (10, 9)
	Radius = 40.0000

)";
	CHECK(output.str() == expected);
}

SCENARIO("Try to find max area and min perimeter shape in empty list")
{
	SECTION("Max area")
	{
		stringstream input, output;
		CCommandHandler handler = CCommandHandler(input, output);
		handler.GetShapeWithMaxArea();
		CHECK(output.str() == "Failed to get the shape with max area. Shapes list is empty.\n");
	}
	SECTION("Min perimeter")
	{
		stringstream input, output;
		CCommandHandler handler = CCommandHandler(input, output);
		handler.GetShapeWithMinPerimeter();
		CHECK(output.str() == "Failed to get the shape with min perimeter. Shapes list is empty.\n");
	}
}