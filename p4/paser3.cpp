#include "expr_parser.h"
#include "lro_table.cpp"


void Parser::parse(){
 stack <pair<Symbol, unsigned int>> pila;
 pila.push(std::pair(Symbol::term,0));
 while(!pila.empty())
 {
  int estado =pila.top().second;
 const PAction & Paccion = lr_action(estado, currToken) ;
 Symbol sym=pila.top().first;
 if(Paccion.isReduce())
 {
    int indice= Paccion.getValue();
    const Rule& r=rule(indice);
    for(int x=0;x<r.rhs.size();x++)
        pila.pop();
    }
    unsigned int siguienteEstado= lr_goto(pila.top().second, r.lhs);
    if(siguienteEstado!=-1)
    pila.push(std::pair(r.lhs,siguienteEstado));
    else
    throw("error");
    
 }
 else if(Paccion.isShift())
 {
     pila.push(std::pair(currToken, Paccion.getValue()));
 }
 else if(Paccion.isAccept())
 {
     return;
 }
 }

}
