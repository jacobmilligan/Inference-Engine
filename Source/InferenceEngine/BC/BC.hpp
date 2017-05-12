//
// Created by mac on 12/05/17.
//

#ifndef IENGINE_BC_HPP
#define IENGINE_BC_HPP

#pragma once

#include "InferenceEngine/Core/Symbol.hpp"
#include "InferenceEngine/Core/KnowledgeBase.hpp"

#include <vector>
#include <queue>
#include <unordered_map>

namespace ie {


    class BC {
    public:
        bool fc_entails(KnowledgeBase& kb, Symbol& q) {

            std::map<std::string, bool> unknownPremise;
            std::stack<Symbol*> truePremises;
            ClauseFinder clause;
            //find symbols in a clause
            for(auto& premise : kb.clauses()){
                premise.second->accept(clause);

            }
        }

        bool is_solvable(KnowledgeBase& kb, ClauseFinder clause){
            for()
        }
    };


}

#endif //IENGINE_BC_HPP
