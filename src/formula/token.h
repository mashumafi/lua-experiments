#ifndef TOKEN
#define TOKEN

#include <string_view>

class Token
{
public:
	enum Type
	{
		TYPE_NONE,
		TYPE_INVALID,
		TYPE_LPAREN,
		TYPE_RPAREN,
		TYPE_QUOTE,
		TYPE_APOS,
		TYPE_PERIOD,
		TYPE_COMMA,
		TYPE_INT,
		TYPE_REAL,
		TYPE_STRING,
		TYPE_ID,
		TYPE_IF,
		TYPE_ADD,
		TYPE_SUB,
		TYPE_MULT,
		TYPE_DIV,
		TYPE_END,
	};

	Token();
	Token(std::string_view token);
	~Token();

	static Token real_type(std::string_view string);
	static Token int_type(std::string_view string);
	static Token string_type(std::string_view string);
	static Token invalid_type(std::string_view string);
	static Token end_type();

	const std::string_view &getString() const;
	Type getType() const;

	bool operator==(const Token& rhs) {
		return m_type == rhs.m_type && m_string == rhs.m_string;
	}
	bool operator!=(const Token& rhs) {
		return m_type != rhs.m_type || m_string != rhs.m_string;
	}

private:
	std::string_view m_string;
	Type m_type;
};

#endif // !TOKEN
