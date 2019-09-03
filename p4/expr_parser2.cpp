#include <vector>
#include "expr_parser.h"

struct Rule {
    Symbol lhs;
    std::vector<Symbol> rhs;
    bool isEmpty() const { return rhs.empty(); }
};

Rule rule0{Symbol::SPrime, {Symbol::S}};
Rule rule1{Symbol::S, {Symbol::OpenBrace, Symbol::L, Symbol::CloseBrace}};
Rule rule2{Symbol::L, {Symbol::L, Symbol::Comma, Symbol::Id}};
Rule rule3{Symbol::L, {Symbol::Id}};
Rule none;

enum ActionType { Accept, Shift, Reduce, Empty };
struct Action {
    Action(): 
        type(ActionType::Empty),
        state(-1),
        rule(none) {}

    Action(ActionType type):
        type(type),
        state(-1),
        rule(none) {}
    
    Action(unsigned state):
        type(ActionType::Shift),
        state(state),
        rule(none) {}
    
    Action(Rule& rule):
        type(ActionType::Reduce),
        state(-1),
        rule(rule) {}
  
      Action(Symbol s):
        type(ActionType::Empty),
        state(-1),
        symbol (s),
        rule(none) {}
        
    Symbol symbol;
    ActionType type;
    int state;
    Rule& rule;
    bool isSymbol(){
        if(state>=0)
        return false;
        else
        return true;
        }
};

Action empty;
Action s1(1);
Action s3(3);
Action s5(5);
Action s6(6);
Action s7(7);
Action r0(rule0); // Reduce rule 0: S' -> S
Action r1(rule1); // Reduce rule 1: S -> { L }
Action r2(rule2); // Reduce rule 2: L -> L , id
Action r3(rule3); // Reduce rule 3: L -> id
Action accept(ActionType::Accept);

/* { } , Id $ */
std::vector<std::vector<Action>> lr0_action = {
    /* State 0 */{ s1, empty, empty, empty, empty },
    /* State 1 */{ empty, empty, empty, s3, empty },
    /* State 2 */{ empty, empty, empty, empty, accept },
    /* State 3 */{ r3, r3, r3, r3, r3 },
    /* State 4 */{ empty, s6, s5, empty, empty },
    /* State 5 */{ empty, empty, empty, s7, empty },
    /* State 6 */{ r1, r1, r1, r1, r1 },
    /* State 7 */{ r2, r2, r2, r2, r2 }
};

/* SPrime S L */
std::vector<std::vector<int>> lr0_goto = {
    /* State 0 */{ -1, 2, -1 }, 
    /* State 1 */{ -1, -1, 4 },
    /* State 2 */{ -1, -1, -1 },
    /* State 3 */{ -1, -1, -1 },
    /* State 4 */{ -1, -1, -1 },
    /* State 5 */{ -1, -1, -1 },
    /* State 6 */{ -1, -1, -1 },
    /* State 7 */{ -1, -1, -1 }
};


int Parser::parse(int count[4]){
    for (int x=0; x < 4; x++)
    {
      count[x] = 0;
    }
    stack<Action> Pila;
    Symbol currentToken = lexer.getNextToken();

    Action start(0);
    Pila.push(start);
    
    while (true) {
        Action actual = Pila.top();        

        if (actual.isSymbol()) {
            int estadoActual = indexOf(actual.symbol);
            stack<Action> Pila2=Pila;
            Pila2.pop();
            Action nuevoEstado(lr0_goto[Pila2.top().state][estadoActual]);
            Pila.push(nuevoEstado);
        } else if (actual.state != -1) {
            Action estadoActual = lr0_action[actual.state][indexOf(currentToken)];
            if (estadoActual.type == ActionType::Reduce) {
                int cant = estadoActual.rule.rhs.size();
                cant = cant << 1;
                for (int i=0; i < cant; i++)
                    Pila.pop();
                Action nuevaAccion(estadoActual.rule.lhs);
                Pila.push(nuevaAccion);
                if (estadoActual.rule.lhs == rule1.lhs)
                    count[0]++;
                else if (estadoActual.rule.rhs == rule2.rhs)
                    count[2]++;
                else if (estadoActual.rule.lhs == rule3.lhs)
                    count[1]++;
            }else if (estadoActual.type == ActionType::Shift) {
                Action nuevaAccion(currentToken);
                Pila.push(nuevaAccion);
                Action segundaAccion(estadoActual.state);
                Pila.push(segundaAccion);
                currentToken = lexer.getNextToken();
            }
            else if (estadoActual.type == ActionType::Accept) {
                count[3]++;
                return 1;
            }
        }
    }
}
