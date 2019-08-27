#ifndef _PARSER_H
#define _PARSER_H

#include <iosfwd>
#include "expr_lexer.h"

struct lr0_data
{
    Symbol simbol;
    int state;

    lr0_data(Symbol s) : simbol(s), state(-1) { }
    lr0_data(int i) : state (i) { }

    bool isSymbol() { return state == -1; }
};

class Parser {
public:
    Parser(Lexer& lexer): lexer(lexer) {}
    int parse(int count[4]);

private:
    Lexer& lexer;

    void printStack(const list<lr0_data>&);
};

#endif
