#pragma once
#include "Resources.h"
#include "CCar.h"

using namespace std;
class CCarRemoteControl
{
public:
	CCarRemoteControl(CCar& myCar, std::istream& input, std::ostream& output);

	~CCarRemoteControl();
	bool CarAutodrive();
	bool Info();
	bool EngineOn();
	bool EngineOff();
	bool SetGear(int gear);
	bool SetSpeed(unsigned int speed);
private:
	
	CCar& m_Car;
	std::istream& m_Input;
	std::ostream& m_Output;

	bool IsInteger(string number);
	vector<string> GetCommand();
	bool HandleCommand();
};

