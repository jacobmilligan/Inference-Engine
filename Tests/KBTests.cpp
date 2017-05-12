//
//  KBTests.cpp
//  iengine
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan on 12/05/2017
//  Copyright (c) 2016 Jacob Milligan. All rights reserved.
//

#define CATCH_CONFIG_RUNNER
#include <catch/catch.hpp>
#include <Path/Path.hpp>
#include <InferenceEngine/Parsing/Parser.hpp>
#include <InferenceEngine/Core/KnowledgeBase.hpp>

sky::Path root("");

ie::Parser parser;
ie::KnowledgeBase kb;

int main(int argc, char** argv)
{
    root.assign(sky::Path::bin_path(argv));
    root.append("../../Tests");

    auto path = root.get_relative("test1.txt");
    auto pre = ie::Parser::preprocess(path);
    parser.parse(pre.tell);
    kb.tell(parser.ast());

    int result = Catch::Session().run(argc, argv);

    return ( result < 0xff ? result : 0xff );
}

TEST_CASE("KB reads all values in", "[kb]")
{
    SECTION("KB gets all clauses")
    {
        std::vector<std::string> clauses = {
            "p2=>p3",
            "p3=>p1",
            "c=>e",
            "b&e=>f",
            "f&g=>h",
            "p1=>d",
            "p1&p3=>c",
            "a",
            "b",
            "p2"
        };

        REQUIRE(clauses.size() == kb.clauses().size());

        for ( auto& c : clauses ) {
            auto result = kb.clauses().find(c);
            auto found = result != kb.clauses().end();
            INFO("Clause:" << c << " Result " << found);
            REQUIRE(found);
        }
    }

    SECTION("KB gets all symbols")
    {
        std::vector<std::string> symbols = {
            "a",
            "b",
            "p2",
            "p3",
            "p1",
            "c",
            "e",
            "f",
            "h",
            "g",
            "d"
        };

        REQUIRE(symbols.size() == kb.symbols().size());

        for ( auto& s : symbols ) {
            auto result = kb.symbols().find(s);
            auto found = result != kb.symbols().end();
            INFO("Clause:" << s << " Result " << found);
            REQUIRE(found);
        }
    }
}