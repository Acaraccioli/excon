#ifndef _PARSER_H
#define _PARSER_H

#include "lexer.h"

class Parser {
public:
    Parser(Lexer& lexer): lexer(lexer) {}
    void parse();
    void input();
    void stmt_list();
    void stmt_list_prime();
    void stmt();
    void expr();
    void expr_prime();
    void term();
    void term_prime();
    void factor();

private:
    Lexer& lexer;
    Token token;
};

#endif
