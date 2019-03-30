#include "token.h"

#include <unordered_map>

std::unordered_map<std::string_view, Token::Type> g_types = {
	{"(", Token::TYPE_LPAREN},
	{")", Token::TYPE_RPAREN},
	{"'", Token::TYPE_APOS},
	{".", Token::TYPE_PERIOD},
	{"\"", Token::TYPE_QUOTE},
	{",", Token::TYPE_COMMA},
	{"IF", Token::TYPE_IF},
	{"ADD", Token::TYPE_ADD},
	{"SUB", Token::TYPE_SUB},
	{"MULT", Token::TYPE_MULT},
	{"DIV", Token::TYPE_DIV},
};

Token::Token()
{
	m_type = Token::TYPE_NONE;
}

Token::Token(std::string_view string)
{
	auto type = g_types.find(string);
	if (type == std::cend(g_types)) {
		m_type = TYPE_ID;
	} else {
		m_type = type->second;
	}
	m_string = string;
}


Token Token::real_type(std::string_view string)
{
	Token tkn;
	tkn.m_string = string;
	tkn.m_type = TYPE_REAL;
	return tkn;
}

Token Token::int_type(std::string_view string)
{
	Token tkn;
	tkn.m_string = string;
	tkn.m_type = TYPE_INT;
	return tkn;
}

Token Token::string_type(std::string_view string)
{
	Token tkn;
	tkn.m_string = string;
	tkn.m_type = TYPE_STRING;
	return tkn;
}

Token Token::invalid_type(std::string_view string)
{
	Token tkn;
	tkn.m_string = string;
	tkn.m_type = TYPE_INVALID;
	return tkn;
}

Token Token::end_type()
{
	Token tkn;
	tkn.m_type = TYPE_END;
	return tkn;
}

Token::~Token()
{
}

const std::string_view &Token::getString() const
{
	return m_string;
}

Token::Type Token::getType() const
{
	return m_type;
}
