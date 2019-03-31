#include <catch.hpp>

#include "datum.h"

TEST_CASE("datum +")
{
	GIVEN("string datum")
	{
		Datum str("Hello");
		WHEN("add int datum")
		{
			Datum i = 123u;
			Datum sum = str + i;
			THEN("should be concatenated")
			{
				REQUIRE(sum == "Hello123");
			}
		}
	}
}

TEST_CASE("datum conversion")
{
	GIVEN("string datum")
	{
		Datum datum("Hello");
		WHEN("cast to string")
		{
			std::string str = datum;
			THEN("should be converted")
			{
				REQUIRE(str == "Hello");
			}
		}
	}
}
