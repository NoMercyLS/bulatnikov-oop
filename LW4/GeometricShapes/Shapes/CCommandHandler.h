#pragma once
#include "IShape.h"
#include "Source.h"
class CCommandHandler
{
public:
	CCommandHandler(std::istream& input, std::ostream& output);
	bool HandleCommand();
	void Info() const;
	void GetShapeWithMinPerimeter() const;
	void GetShapeWithMaxArea() const;
private:
	void AddLineSegment(std::istream& args);
	void AddTriangle(std::istream& args);
	void AddCircle(std::istream& args);
	void AddRectangle(std::istream& args);
	bool CheckIfListIsEmpty() const;
	vector<string> ParseArgs(std::istream& args);
private:
	using ActionMap = map<std::string, function<void(std::istream & args)>>;

	std::istream& m_input;
	std::ostream& m_output;
	std::vector<std::shared_ptr<IShape>> m_shapesList;
	const ActionMap m_actionMap;
};

