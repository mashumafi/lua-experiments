#include "token.h"

#include <unordered_map>

std::unordered_map<std::string_view, Token::Type> g_types = {
	{"(", Token::TYPE_LPAREN},
	{")", Token::TYPE_RPAREN},
	{"[", Token::TYPE_LBRACKET},
	{"]", Token::TYPE_RBRACKET},
	{"!", Token::TYPE_BANG},
	{"'", Token::TYPE_APOS},
	{"\"", Token::TYPE_QUOTE},
	{",", Token::TYPE_COMMA},
	{"IF", Token::TYPE_IF},
	{"ADD", Token::TYPE_ADD},
	{"SUB", Token::TYPE_SUB},
	{"MULT", Token::TYPE_MULT},
	{"DIV", Token::TYPE_DIV},
	{"SUM", Token::TYPE_SUM},
};

Token::Token()
{
}

Token::Token(std::string_view string, std::string_view::size_type offset)
{
	auto type = g_types.find(string);
	if (type == std::cend(g_types)) {
		m_type = TYPE_UNKNOWN;
	} else {
		m_type = type->second;
	}
	m_string = string;
	m_offset = offset;
}

Token::Token(Type type, std::string_view::size_type offset, std::string_view string)
{
	m_type = type;
	m_offset = offset;
	m_string = string;
}

Token Token::real_type(std::string_view string, std::string_view::size_type offset)
{
	return Token(TYPE_REAL, offset, string);
}

Token Token::int_type(std::string_view string, std::string_view::size_type offset)
{
	return Token(TYPE_INT, offset, string);
}

Token Token::string_type(std::string_view string, std::string_view::size_type offset)
{
	return Token(TYPE_STRING, offset, string);
}

Token Token::invalid_type(std::string_view string, std::string_view::size_type offset)
{
	return Token(TYPE_INVALID, offset, string);
}

Token Token::end_type(std::string_view::size_type offset)
{
	return Token(TYPE_END, offset);
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

std::string_view::size_type Token::getOffset() const
{
	return m_offset;
}
