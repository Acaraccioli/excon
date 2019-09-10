#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <sstream>
#include "ExprLexer.h"

enum class State {
    Start_q0,
    Start_q1,
    Operators_q0,
    Numbers_q0,
    Numbers_q1,
    Numbers_q2,
    Numbers_q4,
    Numbers_q5,
    Numbers_q6,
    Punctuation_q0,
    ID_q0,
    ID_q1,
    ID_q2,
};

Symbol ExprLexer::checkKeyword(string text){
    if(text == "print")
        return Symbol::PRINT;
    else
        return Symbol::ID;
}

Symbol ExprLexer::getNextToken() 
{
    text = "";
    State state = State::Start_q0;
    int ch = getNextChar();

    while (true) {
        switch (state) {
            // Start
            case State::Start_q0:
                state = State::Start_q1;
                text="";
                break;
            case State::Start_q1:
                if ((ch == '\n') || (ch == ' ') || (ch == '\t')) {
                    state = State::Start_q1;
                    ch = getNextChar();
                } else if (ch == EOF) {
                    return Symbol::Eof;
                } else {
                    // Trying next automaton 'Operators'
                    state = State::Operators_q0;
                }
                break;
            // Operators
            case State::Operators_q0:
                if (ch == '*') {
                    text += ch;
                    return Symbol::MULT;
                } else if (ch == '/') {
                    text += ch;
                    return Symbol::DIV;
                } else if (ch == '+') {
                    text += ch;
                    return Symbol::SUM;
                } else if (ch == '-') {
                    text += ch;
                    return Symbol::SUB;
                } else {
                    // Trying next automaton 'Numbers'
                    state = State::Numbers_q0;
                }
                break;
            // Numbers
            case State::Numbers_q0:
                if (ch == '0') {
                    text += ch;
                    state = State::Numbers_q4;
                    ch = getNextChar();
                } else if ((ch >= '1') && (ch <= '9')) {
                    text += ch;
                    state = State::Numbers_q1;
                    ch = getNextChar();
                } else {
                    // Trying next automaton 'Punctuation'
                    state = State::Punctuation_q0;
                }
                break;
            case State::Numbers_q1:
                if ((ch >= '0') && (ch <= '9')) {
                    text += ch;
                    state = State::Numbers_q1;
                    ch = getNextChar();
                } else if (ch == '.') {
                    text += ch;
                    state = State::Numbers_q2;
                    ch = getNextChar();
                } else {
                    ungetChar(ch);
                    return Symbol::NUMBER;
                }
                break;
            case State::Numbers_q2:
                if ((ch >= '0') && (ch <= '9')) {
                    text += ch;
                    state = State::Numbers_q2;
                    ch = getNextChar();
                } else {
                    ungetChar(ch);
                    return Symbol::NUMBER;
                }
                break;
            case State::Numbers_q4:
                if (ch == 'x') {
                    text += ch;
                    state = State::Numbers_q5;
                    ch = getNextChar();
                } else if ((ch >= '0') && (ch <= '9')) {
                    text += ch;
                    state = State::Numbers_q1;
                    ch = getNextChar();
                } else {
                    ungetChar(ch);
                    return Symbol::NUMBER;
                }
                break;
            case State::Numbers_q5:
                if (((ch >= '0') && (ch <= '9')) || ((ch >= 'A') && (ch <= 'F')) || ((ch >= 'a') && (ch <= 'f'))) {
                    text += ch;
                    state = State::Numbers_q6;
                    ch = getNextChar();
                } else {
                    // Trying next automaton 'Punctuation'
                    state = State::Punctuation_q0;
                }
                break;
            case State::Numbers_q6:
                if (((ch >= '0') && (ch <= '9')) || ((ch >= 'a') && (ch <= 'f')) || ((ch >= 'A') && (ch <= 'F'))) {
                    text += ch;
                    state = State::Numbers_q6;
                    ch = getNextChar();
                } else {
                    ungetChar(ch);
                    return Symbol::NUMBER;
                }
                break;
            // Punctuation
            case State::Punctuation_q0:
                if (ch == ';') {
                    text += ch;
                    return Symbol::SEMICOLON;
                } else if (ch == '=') {
                    text += ch;
                    return Symbol::ASSIGN;
                } else if (ch == '(') {
                    text += ch;
                    return Symbol::OPEN_PAREN;
                } else if (ch == ')') {
                    text += ch;
                    return Symbol::CLOSE_PAREN;
                } else {
                    // Trying next automaton 'ID'
                    state = State::ID_q0;
                }
                break;
            // ID
            case State::ID_q0:
                if (((ch >= 'a') && (ch <= 'z')) || ((ch >= 'A') && (ch <= 'Z')) || (ch == '_')) {
                    text += ch;
                    state = State::ID_q1;
                    ch = getNextChar();
                } else {
                    reportError(ch);
                    ch = getNextChar();
                    state = State::Start_q0;
                }
                break;
            case State::ID_q1:
                if (((ch >= '0') && (ch <= '9')) || ((ch >= 'a') && (ch <= 'z')) || ((ch >= 'A') && (ch <= 'Z')) || (ch == '_')) {
                    text += ch;
                    state = State::ID_q1;
                    ch = getNextChar();
                } else {
                    return checkKeyword(text);
                }
                break;
        }
    }

}

const char *ExprLexer::tokenToString(Symbol tk)
{
    switch (tk) {
        case Symbol::CLOSE_PAREN: return "CLOSE_PAREN";
        case Symbol::OPEN_PAREN: return "OPEN_PAREN";
        case Symbol::NUMBER: return "NUMBER";
        case Symbol::ASSIGN: return "ASSIGN";
        case Symbol::SUB: return "SUB";
        case Symbol::ID: return "ID";
        case Symbol::Eof: return "Eof";
        case Symbol::PRINT: return "PRINT";
        case Symbol::MULT: return "MULT";
        case Symbol::SUM: return "SUM";
        case Symbol::SEMICOLON: return "SEMICOLON";
        case Symbol::DIV: return "DIV";
        default: return "Unknown";
    }

}