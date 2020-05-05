#pragma once
#include "Resources.h"
#include "CCar.h"
class CCarRemoteControl
{
public:
	CCarRemoteControl(CCar& myCar, std::istream& input, std::ostream& output);
	bool Info();
	bool EngineOn();
	bool EngineOff();
	bool SetGear(int gear);
	bool SetSpeed(int speed);
private:
	
	using ActionMap = std::map<std::string, std::function<void(std::istream & args)>>;
	CCar& m_Car;
	std::istream& m_Input;
	std::ostream& m_Output;

	const ActionMap m_actionMap;
};

