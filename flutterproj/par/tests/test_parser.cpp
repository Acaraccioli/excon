#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <sstream>
#include <memory>
#include <vector>
#include <cstring>
#include "doctest.h"
#include "expr_parser.h"

std::vector<SymbolInfo> genError = { 
    {Symbol::Ident, "x"}
};

std::vector<SymbolInfo> test1 = {
    {Symbol::Number, "45.0"},
    {Symbol::OpAdd, "+"},
    {Symbol::Number, "10.0"},
    {Symbol::Semicolon, ";"},
    {Symbol::Eof, "<<EOF>>"},
};

std::vector<SymbolInfo> test2 = {
    {Symbol::OpenPar, "("},
    {Symbol::Number, "0.535"},
    {Symbol::OpSub, "-"},
    {Symbol::Number, "0.035"},
    {Symbol::ClosePar, ")"},
    {Symbol::OpMul, "*"},
    {Symbol::Number, "10.0"},
    {Symbol::Semicolon, ";"},
    {Symbol::Eof, "<<EOF>>"},
};

std::vector<SymbolInfo> test3 = {
    {Symbol::OpenPar, "("},
    {Symbol::Number, "0.535"},
    {Symbol::OpSub, "-"},
    {Symbol::Number, "0.035"},
    {Symbol::ClosePar, ")"},
    {Symbol::OpMul, "*"},
    {Symbol::Number, "100.0"},
    {Symbol::Semicolon, ";"},
    {Symbol::OpenPar, "("},
    {Symbol::Number, "0.4"},
    {Symbol::OpAdd, "+"},
    {Symbol::Number, "0.6"},
    {Symbol::ClosePar, ")"},
    {Symbol::OpDiv, "/"},
    {Symbol::Number, "4"},
    {Symbol::Semicolon, ";"},
    {Symbol::Eof, "<<EOF>>"},
};

bool genExceptionOnError() {
    Lexer el(genError);
    Parser ep(el);
    
    bool res;
    try {
        ep.parse();
        res = false;
    } catch (...) {
        res = true;
    }
    return res;
}

TEST_CASE("Add expression") {
    REQUIRE(genExceptionOnError());
    
    Lexer l(test1);
    Parser p(l);
    
    bool parseSuccess = false;
    int exprCount = 0;
    try {
        exprCount = p.parse();
        parseSuccess = true;
    } catch (...) {
        parseSuccess = false;
    }
    REQUIRE(!l.hasTokens());
    CHECK(parseSuccess);
    CHECK(exprCount == 1);
}

TEST_CASE("Sub/Mult expression") {
    REQUIRE(genExceptionOnError());
    
    Lexer l(test2);
    Parser p(l);
    
    bool parseSuccess = false;
    int exprCount = 0;
    try {
        exprCount = p.parse();
        parseSuccess = true;
    } catch (...) {
        parseSuccess = false;
    }
    REQUIRE(!l.hasTokens());
    CHECK(parseSuccess);
    CHECK(exprCount == 1);
}

TEST_CASE("Multiple expressions") {
    REQUIRE(genExceptionOnError());
    
    Lexer l(test3);
    Parser p(l);
    
    bool parseSuccess = false;
    int exprCount = 0;
    try {
        exprCount = p.parse();
        parseSuccess = true;
    } catch (...) {
        parseSuccess = false;
    }
    REQUIRE(!l.hasTokens());
    CHECK(parseSuccess);
    CHECK(exprCount == 2);
}

