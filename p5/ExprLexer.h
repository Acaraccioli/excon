#include <fstream>
#include <iostream>
#include <string>

#include "Tokens.h"

using namespace std;

class ExprLexer
{
public:
    ExprLexer(ifstream& in): in(in), line(1) {}
    Symbol getNextToken();
    string getText() { return text; }
    const char* tokenToString(Symbol tk);

private:
    ifstream& in;
    int line;
    string text;

    Symbol checkKeyword(string text);

    int getNextChar() { return in.get(); }

    void ungetChar(char c) { in.unget(); }

    void reportError(char c) {
        std::cerr << "Error at line " << line << " with '" << c << "'\n";
    }
};