//
// Created by mac on 5/05/17.
//

#ifndef PROJECT_AGENT_HPP
#define PROJECT_AGENT_HPP


#include <vector>
#include "InferenceEngine/Core/Symbol.hpp"
#include "InferenceEngine/TT/TruthTable.hpp"
#include "InferenceEngine/Core/Response.hpp"

namespace ie {

    class Agent {
    private:

        int iterations = 0;
        //Count for number of entailments calculated between truthtable and modal query
        int successfulEntailments_;

        //Recursive DFS iteration of truthtable symbols - returning true if modalA is entailed
        //The propert successfulEntailments is incremented for each successful solution
        bool TTCheckALL(std::vector<Symbol *>& modalA,
                        std::vector<Symbol *> symbols, std::vector<Symbol *> partialModelVal, matrix knowledgeBase);

        //Enumerates modelA over the truthtable
        //Increments successfulEntialments count for any true rows where modelA exists
        bool PLtrue(std::vector<Symbol *> KB, std::vector<Symbol *> modelA);

        //overloaded function for 1 modal
        bool PLtrueWorld(matrix knowledgeBase, std::vector<Symbol *> modelA);


        //Combine 2 sets of symbols for 1 'ROW' to be used for enumurating the truthtable
        std::vector<Symbol *> CombineSymbolLists(std::vector<Symbol *> s1, std::vector<Symbol *> s2);

        //Get number of successful entailments following a TT entialment
        int EntailMentsNumber();

    public:

        Agent();

        //User Function for requesting entailment information for a set of 'SYMBOLS'
        Response TTentails(std::vector<Symbol *>& modalA, std::vector<Symbol *> KB, std::vector<Symbol *>& rules,
                           matrix knowledgeBase);
    };

}

#endif //PROJECT_AGENT_HPP
