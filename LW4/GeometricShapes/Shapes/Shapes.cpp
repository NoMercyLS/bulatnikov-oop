#include <iostream>
#include "CCommandHandler.h"
#include "constants.h"

int main()
{
	CCommandHandler shapes(cin, cout);

	cout << INIT_MESSAGE;

	while (!cin.eof() && !cin.fail())
	{
		cout << MARKER;
		if (!shapes.HandleCommand())
		{
			cout << UNKNOWN_COMMAND;
		}
	}
	shapes.Info();
	shapes.GetShapeWithMaxArea();
	shapes.GetShapeWithMinPerimeter();

	return 0;
}