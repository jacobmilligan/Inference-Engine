//
//  VisitorTests.cpp
//  iengine
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan on 5/05/2017
//  Copyright (c) 2016 Jacob Milligan. All rights reserved.
//

#include "CoutUtils.hpp"

#include <InferenceEngine/Parsing/Parser.hpp>
#include <InferenceEngine/AST/ClauseFinder.hpp>
#include <InferenceEngine/AST/Private/ASTPrinter.hpp>

#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>
#include <InferenceEngine/AST/ResolutionVisitor.hpp>
#include <InferenceEngine/TT/TruthTable.hpp>
#include <InferenceEngine/AST/SymbolFinder.hpp>
#include "CoutUtils.hpp"
#include <catch/catch.hpp>

TEST_CASE("calc test negation", "[operators]")
{

    CoutUtils cout_utils;
    ie::ASTPrinter printer;


    std::string rules = "!p";

    ie::Parser parser;
    parser.parse(rules);

    ie::ClauseFinder clause;
    ie::SymbolFinder symFind;

    for(auto& a: parser.ast()){
        a->accept(symFind);
        a->accept(clause);
    }

    for ( auto& c : clause.rules() ) {
        c->accept(printer);
    }


    std::vector<ie::Symbol*> observations = std::vector<ie::Symbol*>();
    ie::TruthTable tt = ie::TruthTable(symFind, clause.rules());


    std::vector<ie::Symbol*> _asks;

    ///Asking if p exists when !p already knowledge
    std::vector<ie::Symbol*> ask = std::vector<ie::Symbol*>();
    ask.push_back(new ie::Symbol("p", false));
//    ask.push_back(new ie::Symbol("z", true));

    Response res = tt.ask(ask);

    REQUIRE(!res.Result);
}

TEST_CASE("calc test dysjunction", "[operators]")
{

    CoutUtils cout_utils;
    ie::ASTPrinter printer;


    std::string rules = "p | q; !p; q";

    ie::Parser parser;
    parser.parse(rules);

    ie::ClauseFinder clause;
    ie::SymbolFinder symFind;

    for(auto& a: parser.ast()){
        a->accept(symFind);
        a->accept(clause);
    }

    for ( auto& c : clause.rules() ) {
        c->accept(printer);
    }


    std::vector<ie::Symbol*> observations = std::vector<ie::Symbol*>();
    ie::TruthTable tt = ie::TruthTable(symFind, clause.rules());


    std::vector<ie::Symbol*> _asks;

    ///Asking if p exists when !p already knowledge
    std::vector<ie::Symbol*> ask = std::vector<ie::Symbol*>();
    ask.push_back(new ie::Symbol("q", false));
//    ask.push_back(new ie::Symbol("z", true));

    Response res = tt.ask(ask);

    REQUIRE(!res.Result);
}