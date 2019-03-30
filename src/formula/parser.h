#ifndef PARSER
#define PARSER

#include "lexer.h"

class Parser
{
public:
	Parser(Lexer& lexer);
	~Parser();

private:
	Lexer& m_lexer;
};

#endif // !PARSER
