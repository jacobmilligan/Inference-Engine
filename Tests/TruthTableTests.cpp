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

    ie::KnowledgeBase kb;
    kb.tell(parser.ast());

    SECTION("world with p = true doesn't exist"){
        ie::TruthTable tt;
        ///Asking if p exists when !p already knowledge
        auto res = tt.ask(kb, ie::Symbol("p", true));

        REQUIRE(!res.result);
    }

    SECTION("world with z  doesn't exist"){
        ie::TruthTable tt;
        ///Asking if p exists when !p already knowledge
        auto res = tt.ask(kb, ie::Symbol("z", true));
        REQUIRE(!res.result);
    }
}


TEST_CASE("calc test disunction", "[operators]")
{
    std::string rules = "p | q;p";

    ie::Parser parser;
    parser.parse(rules);

    ie::KnowledgeBase kb;
    kb.tell(parser.ast());

    ///Asking if p exists when !p already knowledge

    ie::TruthTable tt;
    auto res = tt.ask(kb, ie::Symbol("p", true));

    REQUIRE(res.result);
}

TEST_CASE("calc test conjunction", "[operators]")
{
    std::string rules = "p & q;";

    ie::Parser parser;
    parser.parse(rules);

    ie::KnowledgeBase kb;
    kb.tell(parser.ast());

    //Can exist as we have a possible world where this could be
    ie::TruthTable tt;
    auto res = tt.ask(kb, ie::Symbol("p", true));
    REQUIRE(res.result);
}

TEST_CASE("calc test conjunction 2", "[operators]")
{

    std::string rules = "p & q; a & p; !a; !p;";

    ie::Parser parser;
    parser.parse(rules);

    ie::KnowledgeBase kb;
    kb.tell(parser.ast());

    //a & p are false therefore q should be true
    SECTION("world where q is true"){
        ie::TruthTable tt;
        auto res = tt.ask(kb, ie::Symbol("q", true));
        REQUIRE(res.result);
    }
}

TEST_CASE("calc test combinations", "[operators]")
{
    std::string rules = "p => q; a => p; !a; p";

    ie::Parser parser;
    parser.parse(rules);

    ie::KnowledgeBase kb;
    kb.tell(parser.ast());

    // !a implies truth in implications
    SECTION("world where q is true"){
        ie::TruthTable tt;
        auto res = tt.ask(kb, ie::Symbol("q", true));
        REQUIRE(res.result);
    }
}

TEST_CASE("calc test combinations 2", "[operators]")
{

    std::string rules = "a & b => c; !c";

    ie::Parser parser;
    parser.parse(rules);

    ie::KnowledgeBase kb;
    kb.tell(parser.ast());

    // !c implies that we cannot say if either a or b are true
    SECTION("world where a is false"){
        ie::TruthTable tt;
        auto res = tt.ask(kb, ie::Symbol("a", false));
        REQUIRE(!res.result);
    }

    // !c implies that we cannot say if either a or b are true
    SECTION("world where b is false"){
        ie::TruthTable tt;
        auto res = tt.ask(kb, ie::Symbol("b", false));
        REQUIRE(!res.result);
    }
}

TEST_CASE("calc test combinations 3", "[operators]")
{

    std::string rules = "(p =>  q) & (c => p) & c";

    ie::Parser parser;
    parser.parse(rules);

    ie::KnowledgeBase kb;
    kb.tell(parser.ast());

    // !a implies truth in implications
    SECTION("world where q is true"){
        ie::TruthTable tt;
        auto res = tt.ask(kb, ie::Symbol("q", true));
        REQUIRE(res.result);
    }
}

TEST_CASE("calc test combinations 4 (example case)", "[operators]")
{

    std::string rules = "p2=> p3; p3 => p1; c => e; b&e => f; f&g => h; p1=>d; p1&p3 => c; a; b; p2;";

    ie::Parser parser;
    parser.parse(rules);

    ie::KnowledgeBase kb;
    kb.tell(parser.ast());

    // !a implies truth in implications
    SECTION("world where d is true"){
        ie::TruthTable tt;
        auto res = tt.ask(kb, ie::Symbol("d", true));
        REQUIRE(res.result);
        REQUIRE(res.models_inferred == 3);
    }
}


TEST_CASE("calc test combinations 5 - hard case", "[operators]")
{

    std::string rules = "p7 & p15 => p3; p3 => p1; z => e; !b&e => f; f&!g => h; p1=>d; p1&p3 => p10; !a; b; !p2; p15; p; pp; p7; !e";

    ie::Parser parser;
    parser.parse(rules);

    ie::KnowledgeBase kb;
    kb.tell(parser.ast());

    // !a implies truth in implications
    SECTION("world where p10 is true"){
        ie::TruthTable tt;
        auto res = tt.ask(kb, ie::Symbol("p10", true));
        REQUIRE(res.result);
    }

}