#ifndef __SIMBOLOS_H__
#define __SIMBOLOS_H__

enum class Symbol: unsigned {
    input = 0,
    stmt_list = 1,
    expr = 2,
    stmt_list_prime = 3,
    term = 4,
    expr_prime = 5,
    factor = 6,
    term_prime = 7,
    Eof = 8,
    Semicolon = 9,
    OpAdd = 10,
    OpSub = 11,
    OpMul = 12,
    OpDiv = 13,
    Number = 14,
    Ident = 15,
    OpenPar = 16,
    ClosePar = 17,
    Epsilon = 18
};

static inline unsigned indexOf(Symbol s) {
    unsigned index = static_cast<unsigned>(s);
    if (index < 8) return index;
    else return (index - 8);
}

static inline bool isTerminal(Symbol s) {
    return static_cast<unsigned>(s) >= 8;
}

#endif
