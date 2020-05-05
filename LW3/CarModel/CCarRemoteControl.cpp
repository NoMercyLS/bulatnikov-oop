#include "CCarRemoteControl.h"
#include "Resources.h"
#include "CCar.h"
using namespace std;
using namespace std::placeholders;

CCarRemoteControl::CCarRemoteControl(CCar& myCar, istream& input, ostream& output)
	: m_Car(myCar)
	, m_Input(input)
	, m_Output(output)
{
}

CCarRemoteControl::~CCarRemoteControl()
{
}

bool CCarRemoteControl::Info()
{
	return m_Car.CarStatus();
}

bool CCarRemoteControl::EngineOn()
{
	return m_Car.TurnOnEngine();
}

bool CCarRemoteControl::EngineOff()
{
	return m_Car.TurnOffEngine();
}

bool CCarRemoteControl::SetGear(int gear)
{
	return m_Car.SetGear(gear);
}

bool CCarRemoteControl::SetSpeed(unsigned int speed)
{
	return m_Car.SetSpeed(speed);
}

bool CCarRemoteControl::IsInteger(string line)
{
	int count = 0;
	for (auto i : line)
	{
		if (!isdigit(i))
		{
			if (count == 0)
			{
				if (i != '-')
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
		count++;
	}
	return true;
}

vector<string> CCarRemoteControl::GetCommand()
{
	string commandLine;
	m_Input >> commandLine;
	vector<string> command(2, "");
	if (commandLine == "Exit" || commandLine == "Info" || commandLine == "EngineOn" || commandLine == "EngineOff")
	{
		command[0] = commandLine;
		return command;
	}
	
	if (commandLine == "SetGear" || commandLine == "SetSpeed")
	{
		command[0] = commandLine;
		m_Input >> commandLine;
		command[1] = commandLine;
		return command;
	}
	return command;
}

bool CCarRemoteControl::HandleCommand()
{
	vector<string> command = GetCommand();
	if (command[0] == "Exit")
	{
		exit(0);
	}
	if (command[0] == "Info")
	{
		cout << "Information: \n";
		return CCarRemoteControl::Info();
	}
	if (command[0] == "EngineOn")
	{
		if (CCarRemoteControl::EngineOn())
		{
			cout << "Enngine turned on!\n";
			return true;
		}
		return false;
	}
	if (command[0] == "EngineOff")
	{
		if (CCarRemoteControl::EngineOff())
		{
			cout << "Enngine turned off!\n";
			return true;
		}
		return false;
	}
	if (command[0] == "SetSpeed")
	{
		if (CCarRemoteControl::IsInteger(command[1]))
		{
			if (CCarRemoteControl::SetSpeed(stoul(command[1])))
			{
				cout << "Speed was changed to " << stoi(command[1]) << '\n';
				return true;
			}
			cout << "Speed wasn't changed\n";
			return false;
		}
		else
		{
			return false;
		}
	}
	if (command[0] == "SetGear")
	{
		if (CCarRemoteControl::IsInteger(command[1]))
		{
			if (CCarRemoteControl::SetGear(stoi(command[1])))
			{
				cout << "Gear was changed to " << command[1] << '\n';
				return true;
			}
			cout << "Gear wasn't changed\n";
			return false;
		}
	}
	return false;
}

bool CCarRemoteControl::CarAutodrive()
{
	while (true)
	{
		cout << ">";
		if (!HandleCommand())
		{
			cout << "Command not executed\n";
		}
	}
	return false;
}

