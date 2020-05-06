#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../CarModel/CCar.h"
#include "../CarModel/Resources.h"

TEST_CASE("Settings at start must be default")
{
	CCar Car;
	REQUIRE(!Car.GetEngineStatus());
	REQUIRE(Car.GetGear() == 0);
	REQUIRE(Car.GetMovementDirection() == 0);
	REQUIRE(Car.GetSpeed() == 0);
}

TEST_CASE("Can't set anything while engine turned off")
{
	CCar Car;
	REQUIRE(!Car.SetGear(1));
	REQUIRE(!Car.SetSpeed(10));
	REQUIRE(!Car.SetGear(2));
	REQUIRE(!Car.SetSpeed(50));
	REQUIRE(!Car.SetGear(0));
	REQUIRE(!Car.SetSpeed(100));
}

TEST_CASE("Speed must be in certain range")
{
	CCar Car;
	CHECK(Car.TurnOnEngine());

	CHECK(Car.SetGear(-1));
	CHECK(Car.SetSpeed(20));
	CHECK(Car.SetSpeed(0));
	CHECK(Car.SetGear(0));

	CHECK(Car.SetGear(1));
	CHECK(Car.SetSpeed(20));

	CHECK(Car.GetSpeed() == 20);
	CHECK(Car.SetGear(2));
	CHECK(Car.SetSpeed(30));

	CHECK(Car.SetGear(3));
	CHECK(Car.SetSpeed(40));

	CHECK(Car.SetGear(4));
	CHECK(Car.SetSpeed(50));

	CHECK(Car.SetGear(5));
	CHECK(Car.SetSpeed(150));

	CHECK(Car.SetGear(0));
	CHECK(Car.SetSpeed(140));
	CHECK(!Car.SetSpeed(145));
	CHECK(Car.SetSpeed(0));

}

TEST_CASE("Directional changing")
{
	CCar Car;
	Car.TurnOnEngine();
	SECTION("Gear == 0, Speed == 0 -> Direction = 0")
	{
		CHECK(Car.GetGear() == 0);
		CHECK(Car.GetSpeed() == 0);
		CHECK(Car.GetMovementDirection() == 0);
	}

	SECTION("Gear > 0, Speed > 0 -> Direction = 1")
	{
		CHECK(Car.SetGear(1));
		CHECK(Car.SetSpeed(1));
		CHECK(Car.GetMovementDirection() == 1);
	}

	SECTION("Gear < 0, Speed > 0 -> Direction = -1")
	{
		CHECK(Car.SetGear(-1));
		CHECK(Car.SetSpeed(1));
		CHECK(Car.GetMovementDirection() == -1);
	}
}

TEST_CASE("Engine can be turned off when speed == 0 and gear == 0 only")
{
	CCar Car;
	REQUIRE(Car.TurnOnEngine());
	CHECK(Car.SetGear(1));
	CHECK(Car.SetSpeed(1));
	REQUIRE(!Car.TurnOffEngine());

	CHECK(Car.SetSpeed(0));
	CHECK(Car.SetGear(0));
	REQUIRE(Car.TurnOffEngine());
}

TEST_CASE("Can set reverse gear only when speed == 0")
{
	CCar Car;
	Car.TurnOnEngine();
	Car.SetGear(1);
	Car.SetSpeed(10);
	REQUIRE(!Car.SetGear(-1));
	Car.SetSpeed(0);
	REQUIRE(Car.SetGear(-1));
}

TEST_CASE("Only speed decreasing on neutral gear")
{
	CCar Car;
	Car.TurnOnEngine();
	Car.SetGear(1);
	Car.SetSpeed(30);
	CHECK(Car.SetGear(0));
	CHECK(!Car.SetSpeed(31));
	CHECK(Car.SetSpeed(20));
}