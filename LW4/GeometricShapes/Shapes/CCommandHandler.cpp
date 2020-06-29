#include "CCommandHandler.h"
#include "CCommandHandler.h"
#include "CPoint.h"
#include "CLineSegment.h"
#include "CTriangle.h"
#include "CCircle.h"
#include "CRectangle.h"
#include "constants.h"

using namespace std::placeholders;

CCommandHandler::CCommandHandler(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
	, m_actionMap({
		{"Triangle", bind(&CCommandHandler::AddTriangle, this, _1)},
		{"Circle", bind(&CCommandHandler::AddCircle, this, _1)},
		{"Rectangle", bind(&CCommandHandler::AddRectangle, this, _1)},
		{"LineSegment", bind(&CCommandHandler::AddLineSegment, this, _1)},
		})
{
}

bool CCommandHandler::HandleCommand()
{
	string commandLine;
	getline(m_input, commandLine);
	istringstream strm(commandLine);

	string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		it->second(strm);
		return true;
	}

	return false;
}

void CCommandHandler::Info() const
{
	if (!CheckIfListIsEmpty())
	{
		m_output << ALL_SHAPES_MESSAGE;
	}
	for (const auto shape : m_shapesList)
	{
		m_output << shape->ToString() << endl;
	}
}

void CCommandHandler::AddLineSegment(istream& args)
{
	uint32_t lineColor = DEFAULT_OUTLINE_COLOR;

	vector<string> shapeParametrs = ParseArgs(args);
	CPoint startPoint = { stod(shapeParametrs[1]), stod(shapeParametrs[2]) };
	CPoint endPoint = { stod(shapeParametrs[3]), stod(shapeParametrs[4]) };

	if (shapeParametrs.size() == 6 || shapeParametrs.size() == 5)
	{
		if (shapeParametrs.size() == 6)
		{
			lineColor = stoul(shapeParametrs[5], nullptr, 16);
		}
		auto lineSegment = make_shared<CLineSegment>(startPoint, endPoint, lineColor);
		m_shapesList.push_back(lineSegment);
	}
	else
	{
		m_output << FAIL_LINE_CREATE_MESSAGE;
	}
}

void CCommandHandler::AddTriangle(istream& args)
{
	uint32_t outlineColor = DEFAULT_OUTLINE_COLOR;
	uint32_t fillColor = DEFAULT_FILL_COLOR;

	vector<string> shapeParametrs = ParseArgs(args);

	CPoint vertex1 = { stod(shapeParametrs[1]), stod(shapeParametrs[2]) };
	CPoint vertex2 = { stod(shapeParametrs[3]), stod(shapeParametrs[4]) };
	CPoint vertex3 = { stod(shapeParametrs[5]), stod(shapeParametrs[6]) };
	if (shapeParametrs.size() == 7 || shapeParametrs.size() == 8 || shapeParametrs.size() == 9)
	{
		if (shapeParametrs.size() == 8)
		{
			outlineColor = stoul(shapeParametrs[7], nullptr, 16);
		}
		if (shapeParametrs.size() == 9)
		{
			outlineColor = stoul(shapeParametrs[7], nullptr, 16);
			fillColor = stoul(shapeParametrs[8], nullptr, 16);
		}

		auto triangle = make_shared<CTriangle>(vertex1, vertex2, vertex3, fillColor, outlineColor);
		m_shapesList.push_back(triangle);
	}
	else
	{
		m_output << FAIL_TRIANGLE_CREATE_MESSAGE;
	}
}

void CCommandHandler::AddCircle(istream& args)
{
	uint32_t outlineColor = DEFAULT_OUTLINE_COLOR;
	uint32_t fillColor = DEFAULT_FILL_COLOR;

	vector<string> shapeParametrs = ParseArgs(args);

	CPoint center = { stod(shapeParametrs[1]), stod(shapeParametrs[2]) };
	double radius = stod(shapeParametrs[3]);
	if (shapeParametrs.size() == 4 || shapeParametrs.size() == 5 || shapeParametrs.size() == 6)
	{
		if (shapeParametrs.size() == 5)
		{
			outlineColor = stoul(shapeParametrs[4], nullptr, 16);
		}
		if (shapeParametrs.size() == 6)
		{
			outlineColor = stoul(shapeParametrs[4], nullptr, 16);
			fillColor = stoul(shapeParametrs[5], nullptr, 16);
		}

		auto circle = make_shared<CCircle>(center, radius, fillColor, outlineColor);
		m_shapesList.push_back(circle);
	}
	else
	{
		m_output << FAIL_CIRCLE_CREATE_MESSAGE;
	}
}

void CCommandHandler::AddRectangle(istream& args)
{
	uint32_t outlineColor = DEFAULT_OUTLINE_COLOR;
	uint32_t fillColor = DEFAULT_FILL_COLOR;

	vector<string> shapeParametrs = ParseArgs(args);

	CPoint topLeft = { stod(shapeParametrs[1]), stod(shapeParametrs[2]) };
	double width = stod(shapeParametrs[3]);
	double height = stod(shapeParametrs[4]);
	if (shapeParametrs.size() == 5 || shapeParametrs.size() == 6 || shapeParametrs.size() == 7)
	{
		if (shapeParametrs.size() == 6)
		{
			outlineColor = stoul(shapeParametrs[5], nullptr, 16);
		}
		if (shapeParametrs.size() == 7)
		{
			outlineColor = stoul(shapeParametrs[5], nullptr, 16);
			fillColor = stoul(shapeParametrs[6], nullptr, 16);
		}

		auto rectangle = make_shared<CRectangle>(topLeft, width, height, fillColor, outlineColor);
		m_shapesList.push_back(rectangle);
	}
	else
	{
		m_output << FAIL_RECTANGLE_CREATE_MESSAGE;
	}
}

void CCommandHandler::GetShapeWithMinPerimeter() const
{
	if (!CheckIfListIsEmpty())
	{
		auto shapeWithMinPerimeter = min_element(m_shapesList.begin(), m_shapesList.end(),
			[](shared_ptr<IShape> const& first, shared_ptr<IShape> const& second)
			{
				return second->GetPerimeter() > first->GetPerimeter();
			});
		m_output << SHAPE_MIN_PERIMETER << (*shapeWithMinPerimeter)->ToString() << endl;
	}
	else
	{
		m_output << MIN_PERIMETER_FAIL;
	}

}

void CCommandHandler::GetShapeWithMaxArea() const
{
	if (!CheckIfListIsEmpty())
	{
		auto shapeWithMaxArea = max_element(m_shapesList.begin(), m_shapesList.end(),
			[](shared_ptr<IShape> const& first, shared_ptr<IShape> const& second)
			{
				return second->GetArea() > first->GetArea();
			});
		m_output << SHAPE_MAX_AREA << (*shapeWithMaxArea)->ToString() << endl;
	}
	else
	{
		m_output << MAX_AREA_FAIL;
	}
}

bool CCommandHandler::CheckIfListIsEmpty() const
{
	if (m_shapesList.empty())
	{
		return true;
	}
	return false;
}

vector<string> CCommandHandler::ParseArgs(std::istream& args)
{
	vector<string> shapeParameters;
	string parameter;

	while (getline(args, parameter, ' '))
	{
		shapeParameters.push_back(parameter);
	}
	return shapeParameters;
}