#ifndef _PARSER_H
#define _PARSER_H

#include <iosfwd>
#include "expr_lexer.h"
#include <list>
using namespace std;


class Parser {
public:
    Parser(Lexer& lexer): lexer(lexer) {}
    int parse(int count[4]);

private:
    Lexer& lexer;

};

#endif