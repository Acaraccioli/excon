#include "Parser.h"

void Parser::parse(){
    token = lexer.getNextToken();
    Expression * res = E();

    cout << res->getString() << endl;

    if(token != Symbol::Eof)
        throw "Error";
}

Expression * Parser::E(){

    // std::cout << "Entered E production\n";

    Expression * left = T();

    Expression * right;

    while(token == Symbol::SUM || token == Symbol::SUB){

        // std::cout << "Found sum-sub token\n";

        Symbol temp = token;
        token = lexer.getNextToken();
        right = T();

        if(temp == Symbol::SUM){
            left = new SumExpression(left, right);
            //std::cout << "Made sum expression " << left->getString() << std::endl;
        }
        else{
            // std::cout << "Made sub expression " << left->getString() << std::endl;
            left = new SubExpression(left, right);            
        }
    }

    return left;
}

Expression * Parser::T(){
    // std::cout << "Entered T production\n";

    Expression * left = F();
    Expression * right = nullptr;

    while(token == Symbol::MULT || token == Symbol::DIV){
        Symbol temp = token;
        token = lexer.getNextToken();
        right = F();

        if(temp == Symbol::MULT){
            left = new MultExpression(left, right);
        }
        else{
            left = new DivExpression(left, right);            
        }
    }

    return left;
}

Expression * Parser::F(){

    // std::cout << "Entered F production\n";

    Expression * ret;

    if(token == Symbol::OPEN_PAREN){
        token = lexer.getNextToken();
        ret = E();
        //token = lexer.getNextToken();
    }
    else if(token == Symbol::ID){
        ret = new IDExpression(lexer.getText());
    }
    else if(token == Symbol::NUMBER){
        ret = new NumberExpression(std::stoi(lexer.getText()));
        // std::cout << "Made number expression " << ret->getString() << std::endl;
    }
    else{
        throw std::string("Error");
    }

    token = lexer.getNextToken();

    return ret;
}