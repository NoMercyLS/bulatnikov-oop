#include <iostream>
#include "../../catch2/catch.hpp"
#include "../CarModel/CCarRemoteControl.h"
#include "../CarModel/Resources.h"
using namespace std;

void CommandHandler(CCar& car, const string& command, const string& expected)
{
	stringstream input, output;
	CCarRemoteControl Driver(car, input, output);
	input << command;
	Driver.HandleCommand();
	CHECK(output.str() == expected);
}

TEST_CASE ("Engine on/off")
{
	CCar Car;
	CommandHandler(Car, "EngineOn", "Engine turned on!\n");
	CommandHandler(Car, "EngineOff", "Engine turned off!\n");
}

TEST_CASE("Incorrect commands")
{
	CCar Car;
	CommandHandler(Car, "EngineOff", "");
	Car.TurnOnEngine();
	CommandHandler(Car, "EngineOn", "");
	CommandHandler(Car, "SetSpeed 20", "Speed wasn't changed\n");
	CommandHandler(Car, "SetGear 2", "Gear wasn't changed\n");
}

TEST_CASE("Correct commands")
{
	CCar Car;
	CommandHandler(Car, "EngineOn", "Engine turned on!\n");
	CommandHandler(Car, "SetGear 1", "Gear was changed to 1\n");
	CommandHandler(Car, "SetSpeed 1", "Speed was changed to 1\n");
	CommandHandler(Car, "Info", "Information:\nEngine status: On\nMovement direction: Forward\nCurrent speed: 1\nCurrent gear: 1\n");
}

TEST_CASE("All car statuses from Info command")
{
	CCar Car;
	CommandHandler(Car, "Info", "Information:\nEngine status: Off\nMovement direction: Not move\nCurrent speed: 0\nCurrent gear: 0\n");
	Car.TurnOnEngine();
	Car.SetGear(1);
	Car.SetSpeed(1);
	CommandHandler(Car, "Info", "Information:\nEngine status: On\nMovement direction: Forward\nCurrent speed: 1\nCurrent gear: 1\n");
	Car.SetGear(0);
	Car.SetSpeed(0);
	Car.SetGear(-1);
	Car.SetSpeed(1);
	CommandHandler(Car, "Info", "Information:\nEngine status: On\nMovement direction: Backward\nCurrent speed: 1\nCurrent gear: -1\n");
	Car.SetSpeed(0);
	CommandHandler(Car, "Info", "Information:\nEngine status: On\nMovement direction: Not move\nCurrent speed: 0\nCurrent gear: -1\n");
	Car.SetGear(0);
	Car.TurnOffEngine();
	CommandHandler(Car, "Info", "Information:\nEngine status: Off\nMovement direction: Not move\nCurrent speed: 0\nCurrent gear: 0\n");
}