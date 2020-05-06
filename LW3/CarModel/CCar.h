#pragma once
#include "Resources.h"
using namespace std;
class CCar
{
public:
	CCar();

	~CCar();
	  
	bool CarStatus(ostream& output);
	int GetGear();
	unsigned int GetSpeed();
	bool GetEngineStatus();
	int GetMovementDirection();
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(unsigned int speed);

private:

	bool m_engineStatus;
	int m_movementDirection;
	unsigned int m_currentSpeed;
	int m_currentGear;

};

