#include "lexer.h"

#include <cctype>
#include <algorithm>
#include <functional>

Lexer::Lexer(std::string_view data)
{
	m_data = data;
}

Lexer::~Lexer()
{
}

void Lexer::const_iterator::nextToken()
{
	// find first not-space
	auto start = std::find_if(std::cbegin(m_data), std::cend(m_data), std::not_fn(std::isspace));
	// is it an id
	auto end = std::find_if(start, std::cend(m_data), std::not_fn(std::isalpha));
	if (start != end)
	{
		// we found some alpha, see if there are numbers
		end = std::find_if(end, std::cend(m_data), std::not_fn(std::isdigit));
		m_token = Token(m_data.substr(start - std::cbegin(m_data), end - start));
	}
	else
	{
		//could be a number
		end = std::find_if(end, std::cend(m_data), std::not_fn(std::isdigit));
		if (start != end || *end == '.') {
			// could be a real
			if (*end == '.')
			{
				end++;
				// get decimal
				end = std::find_if(end, std::cend(m_data), std::not_fn(std::isdigit));
				m_token = Token::real_type(m_data.substr(start - std::cbegin(m_data), end - start));
			}
			else
			{
				m_token = Token::int_type(m_data.substr(start - std::cbegin(m_data), end - start));
			}
			// check for invalid, alpha not allowed after
			auto invalid = std::find_if(start, std::cend(m_data), std::not_fn(std::isalpha));
			if (invalid != end)
			{
				end = invalid;
				m_token = Token::invalid_type(m_data.substr(start - std::cbegin(m_data), end - start));
			}
		}
	}
	if (start == m_data.cend())
	{
		m_token = Token::end_type();
	}
	m_data = m_data.substr(end - std::cbegin(m_data), std::cend(m_data) - end);
}

Lexer::const_iterator Lexer::begin() const
{
	return Lexer::const_iterator(m_data);
}

Lexer::const_iterator Lexer::end() const
{
	return Lexer::const_iterator(&Token::end_type());
}
