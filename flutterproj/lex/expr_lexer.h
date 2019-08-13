#ifndef _EXPR_LEXER_H
#define _EXPR_LEXER_H
#include "../fa/lexer.h"
#include <sstream>
using namespace std;
class ExprLexer {
public:
    ExprLexer(std::istream &in) : in(in) {}
   std::istream& in;
   Token getNextToken();
   string text;
    char getNextChar() {
       in.get();
        }
   void ungetChar(int x){
       in.unget();
   }
   void reportError(int x){
   }
   const char * tokenToString(Token tk);

   string getText(){
       return text;
   }
    ~ExprLexer() {}
};
#endif
