#include <iostream>
#include <fstream>

#include "Parser.h"

using namespace std;

int main(int argc, char const *argv[]) {
    if (argc != 2 ) {
        cerr << "Usage: " << argv[0] << " <input file>\n";
        return 1;
    }

    ifstream in(argv[1], ios::in);

    if (!in.is_open()) {
        cerr << "Cannot open input file " << argv[1] << endl;
        return 1;
    }

    ExprLexer lexer(in);
    Parser parser(lexer);

    try{
        std::cout << "Trying to parse\n";
        parser.parse();
        std::cout << "Parsed successfully\n";
    }
    catch(std::string& e){
        cerr << e << endl;
    }

    // ExprLexer lexer(in);
    // Symbol token;

    // while(true) {
    //     token = lexer.getNextToken();
    //     if (token == Symbol::Eof)
    //         break;
    //     cout << lexer.tokenToString(token) << " '" << lexer.getText() << "'\n";
    // }

    in.close();

    return 0;
}