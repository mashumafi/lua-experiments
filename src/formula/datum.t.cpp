#include <catch.hpp>

#include "datum.h"

TEST_CASE("datum", "+")
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