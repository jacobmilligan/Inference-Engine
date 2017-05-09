#include "InferenceEngine/Parsing/Parser.hpp"
#include <Path/Path.hpp>

//For testing atm (cc)
#include <iostream>
#include <cmath>
#include <InferenceEngine/AST/ResolutionVisitor.hpp>
#include <InferenceEngine/AST/ClauseFinder.hpp>
#include <InferenceEngine/AST/SymbolFinder.hpp>
#include "InferenceEngine/Core/Agent.hpp"
#include "InferenceEngine/AST/Private/ASTPrinter.hpp"

void RunTT(const ie::ClauseFinder& c, const ie::SymbolFinder& s);

int main(int argc, char** argv)
{

    auto path = sky::Path(sky::Path::bin_path(argv));
    path.append("../Tests/test5.txt");

    ie::Parser parser;
    auto contents = parser.preprocess(path);
    parser.parse(contents.tell);

    ie::ClauseFinder clause;
    ie::SymbolFinder sFind;

    for(auto& a: parser.ast()){
        a->accept(clause);
    }
    for(auto& a: parser.ast()){
        a->accept(sFind);
    }


    for(auto& str : sFind.get_symbols()){
        std::cout << str << " " << std::endl;
    }


//s
//            std::cout << a;
//            strVec.push_back(a);

    RunTT(clause, sFind);

    return 0;
}


void RunTT(const ie::ClauseFinder& c, const ie::SymbolFinder& symFind){


    //Just all the possible symbols from world i.e. "P" "G" "W" "WT" "P1"
    std::vector<ie::Symbol*> observations = std::vector<ie::Symbol*>();

    //The rules for the world i.e. "P => Q", "W => Q", "^Z => R"
    //symbols_ will also have to be operators too
//    std::vector<ie::Symbol*> rules = std::vector<ie::Symbol*>();


    //Setup a small modal to check against - with 10 true and 1 false
    for(auto& str : symFind.get_symbols()){
        ie::Symbol* s = new ie::Symbol(str, true);
        observations.push_back(s);
    }

    std:: cout << "Telling: " << std::endl;

    for(auto& a : observations){
        std::cout << a->GetSymbolName() << " - " << a->GetValue() << std::endl;
    }
    std::cout << std::endl;


    ie::ASTPrinter printer;

    for(auto& rule : c.rules()){
        std::cout << "rule - ";
        rule->accept(printer);
        std::cout << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Size of tree: " << pow(2, observations.size()) << std::endl;

    ie::TruthTable tt = ie::TruthTable(observations, c.rules());


    //ie::Agent agent = ie::Agent();

    std::vector<ie::Symbol*> ask = std::vector<ie::Symbol*>();
    ask.push_back(new ie::Symbol("p", false));
    ask.push_back(new ie::Symbol("z", true));
    std:: cout << "Asking for: " << std::endl;
    for(auto& a : ask){
        std::cout << a->GetSymbolName() << " - " << a->GetValue() << std::endl;
    }
    std::cout << std::endl;


    Response res = tt.Ask(ask);


    //No rules at the moment
    std::vector<ie::Symbol*> emptyRules = std::vector<ie::Symbol*>();

    //Pass in a.) What we want to know i.e. is this list or symbol true?
    //        b.) Observations -> which is the symbols that are given to us
    //        c.) rules or predicates that we must calculate i.e. P => Q


    clock_t t;    t = clock();
    //Response res = agent.TTentails(ask, observations, emptyRules, tt.GetTruthTableMatrix());
    t = clock() - t;
    printf ("It took %lu clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);

    std::cout << "Infered? " << (res.Result ? "true" : "false") << " , " << "Models infered: " << res.ModalsInfered << std::endl;

}