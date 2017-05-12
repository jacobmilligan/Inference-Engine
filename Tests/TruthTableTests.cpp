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

TEST_CASE("calc single negation and false symbols", "[operators]")
{

    std::string rules = "!p";

    ie::Parser parser;
    parser.parse(rules);

    ie::ClauseFinder clause;
    ie::SymbolFinder symFind;

    for(auto& a: parser.ast()){
        a->accept(symFind);
        a->accept(clause);
    }

    SECTION("world with p = true doesn't exist"){
        std::vector<ie::Symbol*> observations = std::vector<ie::Symbol*>();
        ie::TruthTable tt = ie::TruthTable(symFind, clause.rules());


        std::vector<ie::Symbol*> _asks;

        ///Asking if p exists when !p already knowledge
        std::vector<ie::Symbol*> ask = std::vector<ie::Symbol*>();
        ask.push_back(new ie::Symbol("p", true));

        Response res = tt.ask(ask);

        REQUIRE(!res.Result);
    }

    SECTION("world with z  doesn't exist"){
        std::vector<ie::Symbol*> observations = std::vector<ie::Symbol*>();
        ie::TruthTable tt = ie::TruthTable(symFind, clause.rules());


        std::vector<ie::Symbol*> _asks;
        std::vector<ie::Symbol*> ask = std::vector<ie::Symbol*>();
        ask.push_back(new ie::Symbol("z", true));

        Response res = tt.ask(ask);

        REQUIRE(!res.Result);
    }
}


TEST_CASE("calc test dysjunction", "[operators]")
{
    std::string rules = "p | q;";

    ie::Parser parser;
    parser.parse(rules);

    ie::ClauseFinder clause;
    ie::SymbolFinder symFind;

    for(auto& a: parser.ast()){
        a->accept(symFind);
        a->accept(clause);
    }

    std::vector<ie::Symbol*> observations = std::vector<ie::Symbol*>();
    ie::TruthTable tt = ie::TruthTable(symFind, clause.rules());


    std::vector<ie::Symbol*> _asks;

    ///Asking if p exists when !p already knowledge
    std::vector<ie::Symbol*> ask = std::vector<ie::Symbol*>();
    ask.push_back(new ie::Symbol("q", true));
//  ask.push_back(new ie::Symbol("z", true));

    Response res = tt.ask(ask);

    REQUIRE(res.Result);
}

TEST_CASE("calc test conjunction", "[operators]")
{
    std::string rules = "p & q;";

    ie::Parser parser;
    parser.parse(rules);

    ie::ClauseFinder clause;
    ie::SymbolFinder symFind;

    for(auto& a: parser.ast()){
        a->accept(symFind);
        a->accept(clause);
    }

    //Can exist as we have a possible world where this could be
    SECTION("world where q is true"){
        std::vector<ie::Symbol*> observations = std::vector<ie::Symbol*>();
        ie::TruthTable tt = ie::TruthTable(symFind, clause.rules());


        std::vector<ie::Symbol*> _asks;

        ///Asking if p exists when !p already knowledge
        std::vector<ie::Symbol*> ask = std::vector<ie::Symbol*>();
        ask.push_back(new ie::Symbol("q", true));
//  ask.push_back(new ie::Symbol("z", true));

        Response res = tt.ask(ask);
        REQUIRE(res.Result);
    }
    //Can exist as we have a possible world where this could be
    SECTION("world where p is true"){
        std::vector<ie::Symbol*> observations = std::vector<ie::Symbol*>();
        ie::TruthTable tt = ie::TruthTable(symFind, clause.rules());


        std::vector<ie::Symbol*> _asks;

        ///Asking if p exists when !p already knowledge
        std::vector<ie::Symbol*> ask = std::vector<ie::Symbol*>();
        ask.push_back(new ie::Symbol("p", true));
//  ask.push_back(new ie::Symbol("z", true));

        Response res = tt.ask(ask);
        REQUIRE(res.Result);
    }
}

TEST_CASE("calc test conjunction 2", "[operators]")
{

    std::string rules = "p & q; a & p; !a; !p;";

    ie::Parser parser;
    parser.parse(rules);

    ie::ClauseFinder clause;
    ie::SymbolFinder symFind;

    for(auto& a: parser.ast()){
        a->accept(symFind);
        a->accept(clause);
    }

    //a & p are false therefore q should be true
    SECTION("world where q is true"){
        std::vector<ie::Symbol*> observations = std::vector<ie::Symbol*>();
        ie::TruthTable tt = ie::TruthTable(symFind, clause.rules());


        std::vector<ie::Symbol*> _asks;

        ///Asking if p exists when !p already knowledge
        std::vector<ie::Symbol*> ask = std::vector<ie::Symbol*>();
        ask.push_back(new ie::Symbol("q", true));
//  ask.push_back(new ie::Symbol("z", true));

        Response res = tt.ask(ask);
        REQUIRE(res.Result);
    }
}

TEST_CASE("calc test combinations", "[operators]")
{
    std::string rules = "p => q; a => p; !a";

    ie::Parser parser;
    parser.parse(rules);

    ie::ClauseFinder clause;
    ie::SymbolFinder symFind;

    for(auto& a: parser.ast()){
        a->accept(symFind);
        a->accept(clause);
    }

    // !a inmplies truth in all implications
    SECTION("world where q is true"){
        std::vector<ie::Symbol*> observations = std::vector<ie::Symbol*>();
        ie::TruthTable tt = ie::TruthTable(symFind, clause.rules());


        std::vector<ie::Symbol*> _asks;

        ///Asking if p exists when !p already knowledge
        std::vector<ie::Symbol*> ask = std::vector<ie::Symbol*>();
        ask.push_back(new ie::Symbol("q", true));

        Response res = tt.ask(ask);
        REQUIRE(res.Result);
    }
}

TEST_CASE("calc test combinations 2", "[operators]")
{

    std::string rules = "a & b => c; !c";

    ie::Parser parser;
    parser.parse(rules);

    ie::ClauseFinder clause;
    ie::SymbolFinder symFind;

    for(auto& a: parser.ast()){
        a->accept(symFind);
        a->accept(clause);
    }

    // !c implies that we cannot say if either a or b are true
    SECTION("world where a is false"){
        std::vector<ie::Symbol*> observations = std::vector<ie::Symbol*>();
        ie::TruthTable tt = ie::TruthTable(symFind, clause.rules());


        std::vector<ie::Symbol*> _asks;

        ///Asking if p exists when !p already knowledge
        std::vector<ie::Symbol*> ask = std::vector<ie::Symbol*>();
        ask.push_back(new ie::Symbol("a", false));

        Response res = tt.ask(ask);
        REQUIRE(res.Result);
    }

    // !c implies that we cannot say if either a or b are true
    SECTION("world where b is true"){
        std::vector<ie::Symbol*> observations = std::vector<ie::Symbol*>();
        ie::TruthTable tt = ie::TruthTable(symFind, clause.rules());


        std::vector<ie::Symbol*> _asks;

        ///Asking if p exists when !p already knowledge
        std::vector<ie::Symbol*> ask = std::vector<ie::Symbol*>();
        ask.push_back(new ie::Symbol("b", false));

        Response res = tt.ask(ask);
        REQUIRE(res.Result);
    }
}

TEST_CASE("calc test combinations 3", "[operators]")
{

    std::string rules = "(p =>  q) & (c => p) & c";

    ie::Parser parser;
    parser.parse(rules);

    ie::ClauseFinder clause;
    ie::SymbolFinder symFind;

    for(auto& a: parser.ast()){
        a->accept(symFind);
        a->accept(clause);
    }

    // !c implies that we cannot say if either a or b are true
    SECTION("world where q is true"){
        std::vector<ie::Symbol*> observations = std::vector<ie::Symbol*>();
        ie::TruthTable tt = ie::TruthTable(symFind, clause.rules());


        std::vector<ie::Symbol*> _asks;

        ///Asking if p exists when !p already knowledge
        std::vector<ie::Symbol*> ask = std::vector<ie::Symbol*>();
        ask.push_back(new ie::Symbol("q", true));

        Response res = tt.ask(ask);
        REQUIRE(res.Result);
    }
}

TEST_CASE("calc test combinations 4 (example case)", "[operators]")
{

    std::string rules = "p2=> p3; p3 => p1; c => e; b&e => f; f&g => h; p1=>d; p1&p3 => c; a; b; p2;";

    ie::Parser parser;
    parser.parse(rules);

    ie::ClauseFinder clause;
    ie::SymbolFinder symFind;

    for(auto& a: parser.ast()){
        a->accept(symFind);
        a->accept(clause);
    }
    //ask for d - from exmaple test.txt which we know is true
    SECTION("world where d is true"){
        std::vector<ie::Symbol*> observations = std::vector<ie::Symbol*>();
        ie::TruthTable tt = ie::TruthTable(symFind, clause.rules());


        std::vector<ie::Symbol*> _asks;

        std::vector<ie::Symbol*> ask = std::vector<ie::Symbol*>();
        ask.push_back(new ie::Symbol("d", true));

        Response res = tt.ask(ask);
        REQUIRE(res.Result);
    }
}


TEST_CASE("calc test combinations 5 - hard case", "[operators]")
{

    std::string rules = "p7 & p15 => p3; !p3 => p1; z => e; !b&e => f; f&!g => h; p1=>d; p1&!p3 => p10; !a; b; !p2; p15; p; pp; p7; !e";

    ie::Parser parser;
    parser.parse(rules);

    ie::ClauseFinder clause;
    ie::SymbolFinder symFind;

    for(auto& a: parser.ast()){
        a->accept(symFind);
        a->accept(clause);
    }

    //long chain resulting in p10 true
    SECTION("world where p10 is true"){
        std::vector<ie::Symbol*> observations = std::vector<ie::Symbol*>();
        ie::TruthTable tt = ie::TruthTable(symFind, clause.rules());


        std::vector<ie::Symbol*> _asks;

        std::vector<ie::Symbol*> ask = std::vector<ie::Symbol*>();
        ask.push_back(new ie::Symbol("p10", true));

        Response res = tt.ask(ask);
        REQUIRE(res.Result);
    }

}