#include <catch2/catch.hpp>

#include "lexer.h"

TEST_CASE("Lexer", "nextToken")
{
	std::string_view view = "  hello  world123 (  )( 444,3.14 .14 3. 123abc 1.a 1.2a 2.7  ;  \" test \" ' test ' ' invalid \\' ";
	Lexer lexer(view);
	auto iter = std::cbegin(lexer);

	bool isnone = *iter == Token();
	REQUIRE(isnone);

	iter++;
	REQUIRE(iter->getType() == Token::TYPE_UNKNOWN);
	REQUIRE(std::string(iter->getString()) == "hello");
	REQUIRE(iter->getOffset() == 2);

	iter++;
	REQUIRE(iter->getType() == Token::TYPE_UNKNOWN);
	REQUIRE(std::string(iter->getString()) == "world123");
	REQUIRE(iter->getOffset() == 9);

	iter++;
	REQUIRE(iter->getType() == Token::TYPE_LPAREN);
	REQUIRE(iter->getOffset() == 18);

	iter++;
	REQUIRE(iter->getType() == Token::TYPE_RPAREN);
	REQUIRE(iter->getOffset() == 21);

	iter++;
	REQUIRE(iter->getType() == Token::TYPE_LPAREN);
	REQUIRE(iter->getOffset() == 22);

	iter++;
	REQUIRE(iter->getType() == Token::TYPE_INT);
	REQUIRE(std::string(iter->getString()) == "444");
	REQUIRE(iter->getOffset() == 24);

	iter++;
	REQUIRE(iter->getType() == Token::TYPE_COMMA);
	REQUIRE(iter->getOffset() == 27);

	iter++;
	REQUIRE(iter->getType() == Token::TYPE_REAL);
	REQUIRE(std::string(iter->getString()) == "3.14");
	REQUIRE(iter->getOffset() == 28);

	iter++;
	REQUIRE(iter->getType() == Token::TYPE_REAL);
	REQUIRE(std::string(iter->getString()) == ".14");
	REQUIRE(iter->getOffset() == 33);

	iter++;
	REQUIRE(iter->getType() == Token::TYPE_REAL);
	REQUIRE(std::string(iter->getString()) == "3.");
	REQUIRE(iter->getOffset() == 37);

	iter++;
	REQUIRE(iter->getType() == Token::TYPE_INVALID);
	REQUIRE(std::string(iter->getString()) == "123abc");
	REQUIRE(iter->getOffset() == 40);

	iter++;
	REQUIRE(iter->getType() == Token::TYPE_INVALID);
	REQUIRE(std::string(iter->getString()) == "1.a");
	REQUIRE(iter->getOffset() == 47);

	iter++;
	REQUIRE(iter->getType() == Token::TYPE_INVALID);
	REQUIRE(std::string(iter->getString()) == "1.2a");
	REQUIRE(iter->getOffset() == 51);

	iter++;
	REQUIRE(iter->getType() == Token::TYPE_REAL);
	REQUIRE(std::string(iter->getString()) == "2.7");
	REQUIRE(iter->getOffset() == 56);

	iter++;
	REQUIRE(iter->getType() == Token::TYPE_INVALID);
	REQUIRE(std::string(iter->getString()) == ";");
	REQUIRE(iter->getOffset() == 61);

	iter++;
	REQUIRE(iter->getType() == Token::TYPE_STRING);
	REQUIRE(std::string(iter->getString()) == " test ");
	REQUIRE(iter->getOffset() == 64);

	iter++;
	REQUIRE(iter->getType() == Token::TYPE_STRING);
	REQUIRE(std::string(iter->getString()) == " test ");
	REQUIRE(iter->getOffset() == 73);

	iter++;
	REQUIRE(iter->getType() == Token::TYPE_INVALID);
	REQUIRE(std::string(iter->getString()) == " invalid \\' ");
	REQUIRE(iter->getOffset() == 82);

	iter++;
	REQUIRE(iter->getType() == Token::TYPE_END);
	REQUIRE(iter->getOffset() == 95);

	iter++;
	REQUIRE(iter->getType() == Token::TYPE_END);
	REQUIRE(iter->getOffset() == 95);

	bool isend = std::cend(lexer) == iter;
	REQUIRE(isend);
}
