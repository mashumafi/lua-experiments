#include "lexer.h"

#include <cctype>
#include <algorithm>
#include <functional>
#include <unordered_set>

Lexer::Lexer(std::string_view data)
{
	m_data = data;
}

Lexer::~Lexer()
{
}

int issep(int c) {
	static const std::unordered_set<int> valid = { ',', ')' };
	return valid.find(c) != std::cend(valid) || std::isspace(c);
}

void Lexer::const_iterator::nextToken()
{
	// find first not-space
	auto begin = std::cbegin(m_data) + m_pos;
	auto start = std::find_if(begin, std::cend(m_data), std::not_fn(std::isspace));
	const std::string_view::size_type offset = start - std::cbegin(m_data);
	// is it an id
	auto end = std::find_if(start, std::cend(m_data), std::not_fn(std::isalpha));
	if (start != m_data.cend())
	{
		if (start != end)
		{
			// we found some alpha, see if there are numbers
			end = std::find_if(end, std::cend(m_data), std::not_fn(std::isdigit));
			m_token = Token(m_data.substr(start - std::cbegin(m_data), end - start), offset);
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
					m_token = Token::real_type(m_data.substr(start - std::cbegin(m_data), end - start), offset);
				}
				else
				{
					m_token = Token::int_type(m_data.substr(start - std::cbegin(m_data), end - start), offset);
				}
				// check for invalid, make sure seperator is after
				auto invalid = std::find_if(end, std::cend(m_data), issep);
				if (invalid != end)
				{
					end = invalid;
					m_token = Token::invalid_type(m_data.substr(start - std::cbegin(m_data), end - start), offset);
				}
			}
			else
			{
				// special character
				end = start + 1;
				m_token = Token(m_data.substr(start - std::cbegin(m_data), end - start), offset);
				if (m_token.getType() == Token::TYPE_QUOTE || m_token.getType() == Token::TYPE_APOS)
				{
					start++;
					end = std::find(start, std::cend(m_data), m_token.getString()[0]);
					while (end != std::cend(m_data))
					{
						if (*std::prev(end) != '\\')
						{
							break;
						}
						end++;
						end = std::find(end, std::cend(m_data), m_token.getString()[0]);
					}
					if (end == std::cend(m_data))
					{
						m_token = Token::invalid_type(m_data.substr(start - std::cbegin(m_data), end - start), offset);
					}
					else
					{
						m_token = Token::string_type(m_data.substr(start - std::cbegin(m_data), end - start), offset);
						end++;
					}
				}
				else if (m_token.getType() == Token::TYPE_UNKNOWN)
				{
					m_token = Token::invalid_type(m_token.getString(), offset);
				}
			}
		}
	}
	if (start == m_data.cend())
	{
		m_token = Token::end_type(offset);
	}
	else
	{
		m_pos = end - std::cbegin(m_data);
	}
}

Lexer::const_iterator Lexer::begin() const
{
	return Lexer::const_iterator(m_data);
}

Lexer::const_iterator Lexer::end() const
{
	return Lexer::const_iterator(&Token::end_type(m_data.length()));
}
