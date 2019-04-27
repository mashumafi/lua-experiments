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
		TYPE_UNKNOWN,
		TYPE_LPAREN,
		TYPE_RPAREN,
		TYPE_LBRACKET,
		TYPE_RBRACKET,
		TYPE_BANG,
		TYPE_QUOTE,
		TYPE_APOS,
		TYPE_COMMA,
		TYPE_INT,
		TYPE_REAL,
		TYPE_STRING,
		TYPE_IF,
		TYPE_ADD,
		TYPE_SUB,
		TYPE_MULT,
		TYPE_DIV,
		TYPE_END,
		TYPE_SUM,
	};

	Token();
	Token(std::string_view token, std::string_view::size_type offset);
	virtual ~Token();

	static Token real_type(std::string_view string, std::string_view::size_type offset);
	static Token int_type(std::string_view string, std::string_view::size_type offset);
	static Token string_type(std::string_view string, std::string_view::size_type offset);
	static Token invalid_type(std::string_view string, std::string_view::size_type offset);
	static Token end_type(std::string_view::size_type offset);

	const std::string_view &getString() const;
	Type getType() const;
	std::string_view::size_type getOffset() const;

	bool operator==(const Token& rhs) {
		return m_type == rhs.m_type && m_string == rhs.m_string;
	}
	bool operator!=(const Token& rhs) {
		return m_type != rhs.m_type || m_string != rhs.m_string;
	}

private:
	Token(Type type, std::string_view::size_type offset = 0, std::string_view string = std::string_view());

	Type m_type = TYPE_NONE;
	std::string_view::size_type m_offset = 0;
	std::string_view m_string;
};

#endif // !TOKEN
