
#include "expr_parser.h"
#include "tabla.cpp"
#include <iostream>

using namespace std;
int Parser::parse()
{
    int numexpr=0;;
    currToken=lexer.getNextToken();
    stack<Symbol> MiPila; 
    MiPila.push(Symbol::Eof);
    MiPila.push(Symbol::input);

    while(MiPila.empty()!=true){
        
if(MiPila.top()==Symbol::Epsilon)
             MiPila.pop();     

        if(MiPila.top()==currToken)        {
          

            MiPila.pop();
            
            currToken=lexer.getNextToken();
        }
        else
        {  
            int fila=indexOf(MiPila.top());
            int columna=indexOf(currToken);
           Rule &rule= ll1_table[fila][columna];
           if(rule.isEmpty())
            {
                throw("error");
            }

            else
            {
               if(isTerminal(MiPila.top()))
               {
                                   throw("error");

               }


                MiPila.pop();

             if(rule.rhs.front()!= Symbol::Epsilon)
               {
                  for(auto it=rule.rhs.crbegin(); it!= rule.rhs.crend(); it ++)
               {
                   MiPila.push(*it);
               }
                   
               }
              
               
            }
        }
    }
return numexpr;

}




      


