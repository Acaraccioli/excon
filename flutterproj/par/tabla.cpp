struct Rule {
    Symbol lhs;
    std::vector<Symbol> rhs;
    bool isEmpty() const { return rhs.empty(); }
};

Rule none;
std::vector<std::vector<Rule>> ll1_table = {
    /* input */ { none, none, none, none, none, none, {Symbol::input, {Symbol::stmt_list, }}, {Symbol::input, {Symbol::stmt_list, }}, {Symbol::input, {Symbol::stmt_list, }}, none, },
    /* stmt_list */ { none, none, none, none, none, none, {Symbol::stmt_list, {Symbol::expr, Symbol::Semicolon, Symbol::stmt_list_prime, }}, {Symbol::stmt_list, {Symbol::expr, Symbol::Semicolon, Symbol::stmt_list_prime, }}, {Symbol::stmt_list, {Symbol::expr, Symbol::Semicolon, Symbol::stmt_list_prime, }}, none, },
    /* expr */ { none, none, none, none, none, none, {Symbol::expr, {Symbol::term, Symbol::expr_prime, }}, {Symbol::expr, {Symbol::term, Symbol::expr_prime, }}, {Symbol::expr, {Symbol::term, Symbol::expr_prime, }}, none, },
    /* stmt_list_prime */ { {Symbol::stmt_list_prime, {Symbol::Epsilon, }}, none, none, none, none, none, {Symbol::stmt_list_prime, {Symbol::expr, Symbol::Semicolon, Symbol::stmt_list_prime, }}, {Symbol::stmt_list_prime, {Symbol::expr, Symbol::Semicolon, Symbol::stmt_list_prime, }}, {Symbol::stmt_list_prime, {Symbol::expr, Symbol::Semicolon, Symbol::stmt_list_prime, }}, none, },
    /* term */ { none, none, none, none, none, none, {Symbol::term, {Symbol::factor, Symbol::term_prime, }}, {Symbol::term, {Symbol::factor, Symbol::term_prime, }}, {Symbol::term, {Symbol::factor, Symbol::term_prime, }}, none, },
    /* expr_prime */ { none, {Symbol::expr_prime, {Symbol::Epsilon, }}, {Symbol::expr_prime, {Symbol::OpAdd, Symbol::term, Symbol::expr_prime, }}, {Symbol::expr_prime, {Symbol::OpSub, Symbol::term, Symbol::expr_prime, }}, none, none, none, none, none, {Symbol::expr_prime, {Symbol::Epsilon, }}, },
    /* factor */ { none, none, none, none, none, none, {Symbol::factor, {Symbol::Number, }}, {Symbol::factor, {Symbol::Ident, }}, {Symbol::factor, {Symbol::OpenPar, Symbol::expr, Symbol::ClosePar, }}, none, },
    /* term_prime */ { none, {Symbol::term_prime, {Symbol::Epsilon, }}, {Symbol::term_prime, {Symbol::Epsilon, }}, {Symbol::term_prime, {Symbol::Epsilon, }}, {Symbol::term_prime, {Symbol::OpMul, Symbol::factor, Symbol::term_prime, }}, {Symbol::term_prime, {Symbol::OpDiv, Symbol::factor, Symbol::term_prime, }}, none, none, none, {Symbol::term_prime, {Symbol::Epsilon, }}, },
};
