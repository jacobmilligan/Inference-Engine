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

TEST_CASE("ClauseFinder separates complex and atoms", "[rules]")
{
    CoutUtils cout_utils;

    std::string rules = "p=>q; p; p; q; p&q=>!b; b; !b&!q=>(p|q)&q";
    ie::Parser parser;
    parser.parse(rules);

    ie::ClauseFinder rule_finder;
    ie::ASTPrinter printer;

    for ( auto& n : parser.ast() ) {
        n->accept(rule_finder);
    }

    SECTION("ClauseFinder finds only complex")
    {
        std::vector<std::string> expected = {
            "(p=>q)",
            "p",
            "q",
            "((p&q)=>(!b))",
            "b",
            "(((!b)&(!q))=>((p|q)&q))",
        };

        int index = 0;
        for ( auto& c : rule_finder.rules() ) {
            cout_utils.redirect_cout();
            c->accept(printer);
            REQUIRE(cout_utils.get_cout() == expected[index]);
            cout_utils.reset_cout();
            ++index;
        }
    }

    SECTION("ClauseFinder finds only symbols")
    {
        std::vector<std::string> expected = {
            "p",
            "q",
            "b"
        };

        int index = 0;
        for ( auto& c : rule_finder.symbols() ) {
            REQUIRE(c == expected[index]);
            ++index;
        }
    }


}