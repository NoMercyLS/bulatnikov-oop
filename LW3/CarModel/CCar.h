#pragma once
#include "Resources.h"
class CCar
{
public:
	CCar();

	~CCar();
  
	bool CarStatus();
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

