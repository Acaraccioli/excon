#include <string>

class Expression{

public:
    Expression(){}

    int precedence;

    int getPrec(){
        return precedence;
    }

    void setPrec(int prec){
        precedence = prec;
    }

    virtual std::string getString() = 0;
};

class NumberExpression : public Expression{

public:

    NumberExpression(int value): value(value){
        setPrec(10);
    }

    std::string getString(){
        return std::to_string(value);
    }

    int value;

};

class IDExpression : public Expression{

public:

    IDExpression(std::string value): value(value){
        setPrec(10);
    }

    std::string getString(){
        return value;
    }

    std::string value;

};

class BinaryExpression : public Expression{

public:

    BinaryExpression(Expression * left, Expression * right){
        left_exp = left;
        right_exp = right;
    }

    Expression * left_exp;
    Expression * right_exp;

};

class SumExpression : public BinaryExpression{

public:

    SumExpression(Expression * left, Expression * right) : BinaryExpression(left, right){
        precedence = 0;
    }

    std::string getString(){
        std::string l;
        std::string r;

        if(getPrec() > left_exp->getPrec()){
            l = "(" + left_exp->getString() + ")";
        }
        else{
            l = left_exp->getString();
        }
            
        if(getPrec() > right_exp->getPrec()){
            r = "(" + right_exp->getString() + ")";
        }
        else {
            r = right_exp->getString();
        }

        return l + "+" + r;
    }

};

class SubExpression : public BinaryExpression{

public:

    SubExpression(Expression * left, Expression * right) : BinaryExpression(left, right){
        precedence = 0;
    }

    std::string getString(){
        std::string l;
        std::string r;

        if(getPrec() > left_exp->getPrec()){
            l = "(" + left_exp->getString() + ")";
        }
        else{
            l = left_exp->getString();
        }
            
        if(getPrec() > right_exp->getPrec()){
            r = "(" + right_exp->getString() + ")";
        }
        else {
            r = right_exp->getString();
        }

        return l + "-" + r;
    }

};

class MultExpression : public BinaryExpression{

public:

    MultExpression(Expression * left, Expression * right) : BinaryExpression(left, right){
        precedence = 1;
    }

    std::string getString(){
        std::string l;
        std::string r;

        if(getPrec() > left_exp->getPrec()){
            l = "(" + left_exp->getString() + ")";
        }
        else{
            l = left_exp->getString();
        }
            
        if(getPrec() > right_exp->getPrec()){
            r = "(" + right_exp->getString() + ")";
        }
        else {
            r = right_exp->getString();
        }

        return l + "*" + r;
    }

};

class DivExpression : public BinaryExpression{

public:

    DivExpression(Expression * left, Expression * right) : BinaryExpression(left, right){
        precedence = 1;
    }

    std::string getString(){
        std::string l;
        std::string r;

        if(getPrec() > left_exp->getPrec()){
            l = "(" + left_exp->getString() + ")";
        }
        else{
            l = left_exp->getString();
        }
            
        if(getPrec() > right_exp->getPrec()){
            r = "(" + right_exp->getString() + ")";
        }
        else {
            r = right_exp->getString();
        }

        return l + "/" + r;
    }

};