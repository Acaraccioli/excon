#ifndef __LEXER_H__
#define __LEXER_H__

enum class Token {
    OpenPar,
    ClosePar,
    Number,
    OpSub,
    Eof,
    OpDiv,
    Ident,
    OpMul,
    OpAdd,
};
#endif