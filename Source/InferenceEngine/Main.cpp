#include "InferenceEngine/Parsing/Parser.hpp"
#include <Path/Path.hpp>

//For testing atm (cc)
#include <iostream>
#include <cmath>
#include "InferenceEngine/Core/Agent.hpp"


void RunTT();

int main(int argc, char** argv)
{
    auto path = sky::Path(sky::Path::bin_path(argv));
    path.append("../Tests/test1.txt");

    ie::Parser parser;
    parser.parse(path.str());

    RunTT();

    return 0;
}


void RunTT(){
    //Just all the possible symbols from world i.e. "P" "G" "W" "WT" "P1"
    std::vector<ie::Symbol*> observations = std::vector<ie::Symbol*>();

    //The rules for the world i.e. "P => Q", "W => Q", "^Z => R"
    //symbols_ will also have to be operators too
    std::vector<ie::Symbol*> rules = std::vector<ie::Symbol*>();

    //Setup a small modal to check against - with 10 true and 1 false
    char c;
    for(int i = 0; i < 5; i ++){
        c = 'A' + (char)i;
        std::string str = std::string(1, c);
        ie::Symbol* s = new ie::Symbol(str, true);
        observations.push_back(s);
    }

    std:: cout << "Telling: " << std::endl;

    for(auto& a : observations){
        std::cout << a->GetSymbolName() << " - " << a->GetValue() << std::endl;
    }
    std::cout << std::endl;

    //1 false value
//    c += (char)1;
//    std::string str = std::string(1, c);
//    Symbol* s = new Symbol(str, false);
//    observations.push_back(s);

    std::cout << "Size of tree: " << pow(2, observations.size()) << std::endl;


    ie::TruthTable tt = ie::TruthTable(observations);


    ie::Agent a = ie::Agent();

    std::vector<ie::Symbol*> ask = std::vector<ie::Symbol*>();
    ask.push_back(new ie::Symbol("A", true));
    ask.push_back(new ie::Symbol("B", true));
    ask.push_back(new ie::Symbol("C", false));

    std:: cout << "Asking for: " << std::endl;

    for(auto& a : ask){
        std::cout << a->GetSymbolName() << " - " << a->GetValue() << std::endl;
    }

    std::cout << std::endl;

    //No rules at the moment
    std::vector<ie::Symbol*> emptyRules = std::vector<ie::Symbol*>();

    //Pass in a.) What we want to know i.e. is this list or symbol true?
    //        b.) Observations -> which is the symbols that are given to us
    //        c.) rules or predicates that we must calculate i.e. P => Q


    clock_t t;    t = clock();
    Response res = a.TTentails(ask, observations, emptyRules, tt.GetTruthTableMatrix());
    t = clock() - t;
    printf ("It took %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);

    std::cout << "Infered? " << (res.Result ? "true" : "false") << " , " << "Models infered: " << res.ModalsInfered << std::endl;

}