#include <catch.hpp>

#include "lexer.h"

TEST_CASE("Lexer", "nextToken") {
	std::string_view view = "  hello  world123 (  )( . 444,3.14 .14 3.";
	Lexer lexer(view);
	auto iter = std::cbegin(lexer);

	iter++;
	REQUIRE(iter->getType() == Token::TYPE_ID);
	REQUIRE(std::string(iter->getString()) == "hello");

	iter++;
	REQUIRE(iter->getType() == Token::TYPE_ID);
	REQUIRE(std::string(iter->getString()) == "world123");

	iter++;
	REQUIRE(iter->getType() == Token::TYPE_LPAREN);
	
	iter++;
	REQUIRE(iter->getType() == Token::TYPE_RPAREN);
}
