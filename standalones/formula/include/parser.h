#ifndef PARSER
#define PARSER

#include "lexer.h"

class Parser
{
public:
	Parser(Lexer& lexer);
	virtual ~Parser();

private:
	Lexer& m_lexer;
};

#endif // !PARSER
