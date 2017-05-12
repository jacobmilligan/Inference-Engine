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
    auto path = root.get_relative("test1.txt");
    auto pre = ie::Parser::preprocess(path);
    parser.parse(pre.tell);

    ie::KnowledgeBase kb;
    kb.tell(parser.ast());
}