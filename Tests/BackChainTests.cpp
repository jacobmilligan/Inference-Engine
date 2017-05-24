//
// Created by mac on 19/05/17.
//

#include <InferenceEngine/FC/ForwardChaining.hpp>

#define CATCH_CONFIG_RUNNER
#include <catch/catch.hpp>
#include <InferenceEngine/BC/BackwardChaining.hpp>
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
    auto path = root.get_relative("test6.txt");
    auto pre = ie::Parser::preprocess(path);
    parser.parse(pre.tell);

    ie::BackwardChaining backChain;

    std::map<std::string, bool> newMap;
    ie::KnowledgeBase kb;
    kb.tell(parser.ast());
    std::vector<const ie::ComplexSentence*> rules;
    for(auto a : kb.rules()){
        rules.push_back(a.second);
    }
//    for(auto& a : parser.ast()){
//        a->accept(clause);
//    }

    newMap.insert(std::make_pair("T", true));

    backChain.bc_entails(rules, "G", newMap);

}