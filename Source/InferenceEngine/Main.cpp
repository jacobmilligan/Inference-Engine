#include <InferenceEngine/Parsing/CLIParser.hpp>
#include <Path/Path.hpp>

//For testing atm (cc)
#include <iostream>
#include <cmath>
#include <InferenceEngine/AST/ResolutionVisitor.hpp>
#include <InferenceEngine/AST/ClauseFinder.hpp>
#include <InferenceEngine/AST/SymbolFinder.hpp>
#include <InferenceEngine/BC/BackwardChaining.hpp>
#include "InferenceEngine/AST/Private/ASTPrinter.hpp"

#include <InferenceEngine/Core/IEngine.hpp>
#include <InferenceEngine/AST/Private/ASTPrinter.hpp>


void run_bc(sky::Path path);

int main(int argc, char** argv)
{
    ie::CLIParser cli(sky::Path(argv[0]).filename(),
                      "Infers truths from a horn clause knowledge base");
    cli.add_positional(ie::CLIArgument("method", "The method to use when "
        "inferring the given ASK statement"));
    cli.add_positional(ie::CLIArgument("filename", "The name of the file "
        "(relative to the current working directory) where the knowledge base "
        "file is located"));
    cli.parse(argc, argv);

    auto path = sky::Path(sky::Path::bin_path(argv));
    path.append("../Tests/test6.txt");

//    ie::Parser parser;
//    auto contents = parser.preprocess(path);
//    parser.parse(contents.tell);
//
//    ie::ClauseFinder clause;
//    ie::SymbolFinder sFind;
//
//    for(auto& a: parser.ast()){
//        a->accept(clause);
//    }
//    for(auto& a: parser.ast()){
//        a->accept(sFind);
//    }
//
//
//    for(auto& str : sFind.get_symbols()){
//        std::cout << str << " " << std::endl;
//    }
//
//    //RunTT(clause, sFind);
//
//    return 0;

    run_bc(path);
}


void run_bc(sky::Path path){
    ie::Parser parser;

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

    newMap.insert(std::make_pair("p2", true));

    std::string res = backChain.bc_entails(rules, "d", newMap);

    if(res != ""){
        std::cout << res << std::endl;
    }
}
