#ifndef LEXER
#define LEXER

#include "token.h"

#include <string_view>

class Lexer
{
public:
	class const_iterator
	{
	public:
		using self_type = const_iterator;
		using value_type = Token;
		using reference = Token&;
		using pointer = Token*;
		using difference_type = int;
		using iterator_category = std::forward_iterator_tag;
		const_iterator(pointer ptr) : m_token(*ptr) { }
		const_iterator(std::string_view data) : m_data(data) { }
		self_type operator++() { self_type i = *this; nextToken(); return i; }
		self_type operator++(int junk) { nextToken(); return *this; }
		const reference operator*() { return m_token; }
		const pointer operator->() { return &m_token; }
		bool operator==(const self_type& rhs) { return m_token == rhs.m_token; }
		bool operator!=(const self_type& rhs) { return m_token != rhs.m_token; }
	private:
		std::string_view m_data;
		std::string_view::size_type m_pos = 0;
		Token m_token;
		void nextToken();
	};

	Lexer(std::string_view data);
	~Lexer();

	const_iterator begin() const;
	const_iterator end() const;

private:
	std::string_view m_data;
};

#endif // !LEXER
