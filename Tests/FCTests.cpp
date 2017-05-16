//
//  FCTests.cpp
//  iengine
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan on 12/05/2017
//  Copyright (c) 2016 Jacob Milligan. All rights reserved.
//

#include <InferenceEngine/FC/ForwardChaining.hpp>

#define CATCH_CONFIG_RUNNER
#include <catch/catch.hpp>
#include <Path/Path.hpp>
#include <InferenceEngine/Parsing/Parser.hpp>
#include <InferenceEngine/Core/KnowledgeBase.hpp>

sky::Path root("");

int main(int argc, char** argv)
{
    root.assign(sky::Path::bin_path(argv));
    root.append("../../Tests");

    int result = Catch::Session().run(argc, argv);

    return ( result < 0xff ? result : 0xff );
}

TEST_CASE("Forward chaining works on given test data", "[fc]")
{
    ie::Parser parser;
    std::vector<std::string> expected = { "b", "p2", "a", "p3", "p1", "c", "d" };

    auto path = root.get_relative("test1.txt");
    auto pre = ie::Parser::preprocess(path);
    parser.parse(pre.tell);

    ie::KnowledgeBase kb;
    kb.tell(parser.ast());

    ie::FC fc;
    auto sym = ie::Symbol("d", true);
    auto result = fc.fc_entails(kb, sym);

    REQUIRE(result == true);

    for ( int i = 0; i < fc.path().size(); ++i ) {
        INFO("Index: " << i);
        REQUIRE(fc.path()[i] == expected[i]);
    }
}

TEST_CASE("Forward chaining works on other data", "[fc]")
{
    ie::Parser parser;
    std::vector<std::string> expected = { "b", "a", "p1", "c", "p3", "d" };

    parser.parse("p1=> p3; a; b; a=>p1; p1&a=>c; c=>d");

    ie::KnowledgeBase kb;
    kb.tell(parser.ast());

    ie::FC fc;
    auto sym = ie::Symbol("d", true);
    auto result = fc.fc_entails(kb, sym);

    REQUIRE(result == true);

    for ( int i = 0; i < fc.path().size(); ++i ) {
        INFO("Index: " << i);
        REQUIRE(fc.path()[i] == expected[i]);
    }
}

TEST_CASE("Forward chaining returns false", "[fc]")
{
    ie::Parser parser;
    std::vector<std::string> expected = { "b", "a", "p1", "c", "p3", "d" };

    parser.parse("p1=> p3; a; b; a=>p1; p1&a=>c; c=>d");

    ie::KnowledgeBase kb;
    kb.tell(parser.ast());

    ie::FC fc;
    auto sym = ie::Symbol("x", true);
    auto result = fc.fc_entails(kb, sym);

    REQUIRE(!result);

    for ( int i = 0; i < fc.path().size(); ++i ) {
        INFO("Index: " << i);
        REQUIRE(fc.path()[i] == expected[i]);
    }
}

TEST_CASE("Forward chaining works for all test cases", "[fc]")
{
    ie::Parser parser;
    ie::FC fc;
    ie::KnowledgeBase kb;

    SECTION("Test 1")
    {
        std::vector<std::string> expected = { "b", "a", "l", "m", "p", "q" };
        parser.parse("p=>q; l&m=>p; b & l => m; a&p => l; a&b => l; a; b");

        kb.clear();
        kb.tell(parser.ast());

        auto sym = ie::Symbol("q", true);
        auto result = fc.fc_entails(kb, sym);

        REQUIRE(result);

        for ( int i = 0; i < fc.path().size(); ++i ) {
            INFO("Index: " << i);
            REQUIRE(fc.path()[i] == expected[i]);
        }
    }

    SECTION("Test 2")
    {
        std::vector<std::string> expected = { "b", "a", "l", "r", "m", "p", "q" };
        parser.parse("p|r=>q; l&!m=>p; r & l => m; m&l => q;b=>l; !a&b => r; a; b");

        kb.clear();
        kb.tell(parser.ast());

        auto sym = ie::Symbol("q", true);
        auto result = fc.fc_entails(kb, sym);

        REQUIRE(result);

        for ( int i = 0; i < fc.path().size(); ++i ) {
            INFO("Index: " << i);
            REQUIRE(fc.path()[i] == expected[i]);
        }
    }

    SECTION("Test 3")
    {
        std::vector<std::string> expected = { "b", "a", "l", "r", "m", "q", "p", "z" };
        parser.parse("(p&a)|r=>z; (l&!m)&q=>p; r & l => m; m&l => q;b=>l; !a&b => r; a; b");

        kb.clear();
        kb.tell(parser.ast());

        auto sym = ie::Symbol("z", true);
        auto result = fc.fc_entails(kb, sym);

        REQUIRE(result);

        for ( int i = 0; i < fc.path().size(); ++i ) {
            INFO("Index: " << i);
            REQUIRE(fc.path()[i] == expected[i]);
        }
    }
}