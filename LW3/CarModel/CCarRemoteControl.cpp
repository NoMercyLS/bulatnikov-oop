#include "CCarRemoteControl.h"
#include "Resources.h"
#include "CCar.h"
using namespace std;
using namespace std::placeholders;

CCarRemoteControl::CCarRemoteControl(CCar& myCar, istream& input, ostream& output)
	: m_Car(myCar)
	, m_Input(input)
	, m_Output(output)
	, m_actionMap({ { "Info", bind(&CCarRemoteControl::Info, this, _1)},
		  { "EngineOn", bind(&CCarRemoteControl::EngineOn, this, _1) },
		  { "EngineOff", bind(&CCarRemoteControl::EngineOff, this, _1) },
		  { "SetGear", bind(&CCarRemoteControl::SetGear, this, _1) },
		  { "SetSpeed", bind(&CCarRemoteControl::SetSpeed, this, _1) } })
{
}