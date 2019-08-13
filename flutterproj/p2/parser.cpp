#include "parser.h"

void Parser::parse() {
    token=lexer.getNextToken();
    input();
     if(token!=Token::Eof)
   {
       throw("error");
   }
   
    
}

void Parser::input(){
    stmt_list();
   /*   if(token==Token::Semicolon)
   {
       token=lexer.getNextToken();

   }*/
   
  
}

void Parser::stmt_list(){
           stmt();

       if(token==Token::Semicolon)
   {
       token=lexer.getNextToken();
    stmt_list_prime();
   }  else
   {
       throw("error");
   }
  
  
}

void Parser::stmt_list_prime(){

if(token!=Token::Eof)
{
               stmt();

       if(token==Token::Semicolon)
   {
       token=lexer.getNextToken();
    stmt_list_prime();
   }  else
   {
       throw("error");
   }

}
else
{
    /* code */
}

    

}

void Parser::stmt(){
    if(token==Token::Ident)
    {
        token=lexer.getNextToken();

        if(token==Token::OpAssign)
        {
             token=lexer.getNextToken();
             expr();
        }
        else
        {
            throw("error");
        }
        

    }
    else if (token==Token::KwPrint)
    {
         token=lexer.getNextToken();
         if(token!=Token::OpenPar)
         throw("error");
         expr();

    }
    
    
}

void Parser::expr(){
    term();
    expr_prime();
}

void Parser::expr_prime(){

if(token==Token::OpAdd)
    {
         token=lexer.getNextToken();
         term();
         expr_prime();
    }   
}

void Parser::term(){
    factor();
    term_prime();
}

void Parser::term_prime(){

    if(token==Token::OpMult)
    {
         token=lexer.getNextToken();
         factor();
         term_prime();
    }   
}

void Parser::factor(){

    if(token==Token::Ident)
    {
        token=lexer.getNextToken();
    }
    else if(token==Token::Number)
    {
        token=lexer.getNextToken();
    }
    else if(token==Token::OpenPar)
    {
        token=lexer.getNextToken();
        expr();
        if(token==Token::ClosePar)
     {
         token=lexer.getNextToken();
    }
     else
     {
       throw("error");
       }
       
    }
     else{
         throw("erorr");
     }
}