#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <sstream>
#include "expr_lexer.h"

enum class State {
    start_q0,
    start_q1,
    number_q0,
    number_q1,
    number_q3,
    lcomment_q0,
    lcomment_q1,
    bcomment_q0,
    bcomment_q1,
    bcomment_q2,
    arith_q0,
    arith_q6,
    identifier_q0,
    identifier_q1,
};

Token ExprLexer::getNextToken() 
{
    State state = State::start_q0;
    int ch = getNextChar();

    while (true) {
        switch (state) {
            // start
            case State::start_q0:
                state = State::start_q1;
                text="";
                break;
            case State::start_q1:
                if ((ch == '\n') || (ch == ' ') || (ch == '\t')) {
                    state = State::start_q1;
                    ch = getNextChar();
                } else if (ch == EOF) {
                    return Token::Eof;
                } else {
                    // Trying next automaton 'number'
                    state = State::number_q0;
                }
                break;
            // number
            case State::number_q0:
                if (isdigit(ch)) {
                    text += ch;
                    state = State::number_q1;
                    ch = getNextChar();
                } else {
                    // Trying next automaton 'arith'
                    state = State::arith_q0;
                }
                break;
            case State::number_q1:
                if (isdigit(ch)) {
                    text += ch;
                    state = State::number_q1;
                    ch = getNextChar();
                } else if (ch == '.') {
                    text += ch;
                    state = State::number_q3;
                    ch = getNextChar();
                } else {
                    ungetChar(ch);
                    return Token::Number;
                }
                break;
            case State::number_q3:
                if (isdigit(ch)) {
                    text += ch;
                    state = State::number_q3;
                    ch = getNextChar();
                } else {
                    ungetChar(ch);
                    return Token::Number;
                }
                break;
            // lcomment
            case State::lcomment_q0:
                state = State::lcomment_q1;
                break;
            case State::lcomment_q1:
                if (ch == '\n') {
                    state = State::start_q0;
                    ch = getNextChar();
                } else if (ch == EOF) {
                    return Token::Eof;
                } else {
                    state = State::lcomment_q1;
                    ch = getNextChar();
                }
                break;
            // bcomment
            case State::bcomment_q0:
                state = State::bcomment_q1;
                break;
            case State::bcomment_q1:
                if (ch == '*') {
                    state = State::bcomment_q2;
                    ch = getNextChar();
                } else {
                    state = State::bcomment_q1;
                    ch = getNextChar();
                }
                break;
            case State::bcomment_q2:
                if (ch == ')') {
                    state = State::start_q0;
                    ch = getNextChar();
                } else {
                    state = State::bcomment_q1;
                }
                break;
            // arith
            case State::arith_q0:
                if (ch == '/') {
                    text += ch;
                    return Token::OpDiv;
                } else if (ch == '*') {
                    text += ch;
                    return Token::OpMul;
                } else if (ch == '-') {
                    text += ch;
                    return Token::OpSub;
                } else if (ch == '(') {
                    text += ch;
                    state = State::arith_q6;
                    ch = getNextChar();
                } else if (ch == '+') {
                    text += ch;
                    return Token::OpAdd;
                } else if (ch == ')') {
                    text += ch;
                    return Token::ClosePar;
                } else if (ch == '#') {
                    state = State::lcomment_q0;
                    ch = getNextChar();
                } else {
                    // Trying next automaton 'identifier'
                    state = State::identifier_q0;
                }
                break;
            case State::arith_q6:
                if (ch == '*') {
                    state = State::bcomment_q0;
                    ch = getNextChar();
                } else {
                    ungetChar(ch);
                    return Token::OpenPar;
                }
                break;
            // identifier
            case State::identifier_q0:
                if (ch == '_') {
                    text += ch;
                    state = State::identifier_q1;
                    ch = getNextChar();
                } else {
                    reportError(ch);
                    ch = getNextChar();
                    state = State::start_q0;
                }
                break;
            case State::identifier_q1:
                if ((isdigit(ch)) || (isalpha(ch)) || (ch == '_')) {
                    text += ch;
                    state = State::identifier_q1;
                    ch = getNextChar();
                } else {
                    ungetChar(ch);
                    return Token::Ident;
                }
                break;
        }
    }

}

const char *ExprLexer::tokenToString(Token tk)
{
    switch (tk) {
        case Token::OpenPar: return "OpenPar";
        case Token::ClosePar: return "ClosePar";
        case Token::Number: return "Number";
        case Token::OpSub: return "OpSub";
        case Token::Eof: return "Eof";
        case Token::OpDiv: return "OpDiv";
        case Token::Ident: return "Ident";
        case Token::OpMul: return "OpMul";
        case Token::OpAdd: return "OpAdd";
        default: return "Unknown";
    }

}