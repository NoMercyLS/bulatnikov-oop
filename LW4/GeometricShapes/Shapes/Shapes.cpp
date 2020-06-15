#include <iostream>
#include "CCommandHandler.h"

int main()
{
	CCommandHandler shapes(cin, cout);

	cout << "Enter this commands to create shapes:" << endl
		 << "LineSegment <x1> <y1> <x2> <y2> ( <outline color> )" << endl
		 << "Triangle <x1> <y1> <x2> <y2> <x3> <y3>( <outline color> <fill color> )" << endl
		 << "Circle <x> <y> <radius> ( <outline color> <fill color> )" << endl
		 << "Rectangle <x> <y> <width> <height> ( <outline color> <fill color> )" << endl
		 << "Example: Rectangle 10.3 20.15 30.7 40.4 ff0000 00ff00" << endl;

	while (!cin.eof() && !cin.fail())
	{
		cout << ">";
		if (!shapes.HandleCommand())
		{
			cout << "Unknown command!" << endl;
		}
	}
	shapes.Info();
	shapes.GetShapeWithMaxArea();
	shapes.GetShapeWithMinPerimeter();

	return 0;
}