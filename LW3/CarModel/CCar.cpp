#include "CCar.h"
#include "Resources.h"

CCar::CCar()
	:m_engineStatus(false)
	,m_movementDirection(0)
	,m_currentSpeed(0)
	,m_currentGear(0)
{
}

CCar::~CCar()
{
}

bool CCar::TurnOnEngine()
{
	if (m_engineStatus)
	{
		return false;
	}
	else
	{
		m_engineStatus = true;
		return true;
	}
}

bool CCar::TurnOffEngine()
{
	if (m_engineStatus && m_currentGear == 0 && m_currentSpeed == 0)
	{
		m_engineStatus = false;
		return true;
	}
	else
	{
		return false;
	}
}

bool CCar::SetGear(int gear)
{
	if (gear == m_currentGear)
	{
		return true;
	}
	if (gear == -1)
	{
		if (m_currentSpeed == 0)
		{
			m_currentGear = -1;
			return true;
		}
		else
		{
			return false;
		}
	}
	if (gear == 0)
	{
		m_currentGear = 0;
		return true;
	}
	if (gear == 1)
	{
		if (m_movementDirection == -1)
		{
			if (m_currentSpeed > 0)
			{
				return false;
			}
			m_currentGear = 1;
			return true;
		}
		if (m_movementDirection = 0)
		{
			m_currentGear = 1;
			return true;
		}
		if (m_movementDirection == 1)
		{
			if (m_currentSpeed >= 0 && m_currentSpeed <= 30)
			{
				m_currentGear = 1;
				return true;
			}
		}
	}
	if (gear == 2)
	{
		if (m_currentSpeed >= 20 && m_currentSpeed <= 50)
		{
			m_currentGear = 2;
			return true;
		}
		return false;
	}
	if (gear == 3)
	{
		if (m_currentSpeed >= 30 && m_currentSpeed <= 60)
		{
			m_currentGear = 3;
			return true;
		}
		return false;
	}
	if (gear == 4)
	{
		if (m_currentSpeed >= 40 && m_currentSpeed <= 90)
		{
			m_currentGear = 4;
			return true;
		}
		return false;
	}
	if (gear == 5)
	{
		if (m_currentSpeed >= 50 && m_currentSpeed <= 150)
		{
			m_currentGear = 5;
			return true;
		}
		return false;
	}

	return false;
}

bool CCar::SetSpeed(int speed)
{
	if (speed < 0 && speed > 150)
	{
		return false;
	}
	if (m_currentGear == -1)
	{
		if (speed >= 0 && speed <= 20)
		{
			m_currentSpeed == speed;
			m_movementDirection = -1;
			return true;
		}
		return false;
	}
	if (m_currentGear == 0)
	{
		if (m_currentSpeed < speed)
		{
			return false;
		}
		m_currentSpeed = speed;
		return true;
	}
	if (m_currentGear == 1)
	{
		if (speed >= 0 && speed <= 30)
		{
			m_currentSpeed == speed;
			m_movementDirection = 1;
			return true;
		}
		return false;
	}
	if (m_currentGear == 2)
	{
		if (speed >= 20 && speed <= 50)
		{
			m_currentSpeed == speed;
			m_movementDirection = 1;
			return true;
		}
		return false;
	}
	if (m_currentGear == 3)
	{
		if (speed >= 30 && speed <= 60)
		{
			m_currentSpeed == speed;
			m_movementDirection = 1;
			return true;
		}
		return false;
	}
	if (m_currentGear == 4)
	{
		if (speed >= 40 && speed <= 90)
		{
			m_currentSpeed == speed;
			m_movementDirection = 1;
			return true;
		}
		return false;
	}
	if (m_currentGear == 5)
	{
		if (speed >= 50 && speed <= 150)
		{
			m_currentSpeed == speed;
			m_movementDirection = 1;
			return true;
		}
		return false;
	}
}