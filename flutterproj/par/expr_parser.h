#ifndef _PARSER_H
#define _PARSER_H

#include "expr_lexer.h"
#include "simbolos.h"
#include <stack>

class Parser {
public:
    Parser(Lexer& lexer): lexer(lexer) {}
    int parse();

private:
    Lexer& lexer;
    Symbol currToken;
};

#endif
