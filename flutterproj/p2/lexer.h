#ifndef _LEXER_H
#define _LEXER_H

#include <iostream>
#include <stdexcept>
#include <fstream>
#include <string>
#include <vector>

enum class Token { 
    KwPrint,
    Ident,
    Semicolon,
    OpenPar, 
    ClosePar, 
    OpAssign,
    OpAdd, 
    OpMult, 
    Number, 
    Unknown, 
    Eof
};

using TokenInfo = std::pair<Token, std::string>;

class Lexer {
public:
	Lexer(const std::vector<TokenInfo>& tklst): tklist(tklst) {
        it = tklist.begin();
    }

    Token getNextToken() {
        if (it == tklist.end()) {
            throw std::runtime_error("No more tokens to process");
        }
        
        Token tk = it->first;
        text = it->second;
        it++;
        
        return tk;
    }
    
    bool hasTokens() { return it != tklist.end(); }
    std::string getText() { return text; }

private:
    std::string text;
    std::vector<TokenInfo> tklist;
    std::vector<TokenInfo>::iterator it;
};
#endif
