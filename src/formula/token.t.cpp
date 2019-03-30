#include <catch.hpp>

#include "token.h"

TEST_CASE("Token", "getType") {
	GIVEN("a token") {
		WHEN("token is add") {
			Token tkn("ADD");
			THEN("type is add") {
				CHECK(tkn.getType() == Token::TYPE_ADD);
			}
		}

		WHEN("token is (") {
			Token tkn("(");
			THEN("type is lparen") {
				CHECK(tkn.getType() == Token::TYPE_LPAREN);
			}
		}
	}
}