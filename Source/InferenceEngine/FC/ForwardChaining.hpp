//
//  ForwardChaining.hpp
//  iengine
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan on 12/05/2017
//  Copyright (c) 2016 Jacob Milligan. All rights reserved.
//

#pragma once

#include "InferenceEngine/Core/Symbol.hpp"
#include "InferenceEngine/Core/KnowledgeBase.hpp"

#include <vector>
#include <queue>
#include <unordered_map>

namespace ie {


class FC {
public:
    bool fc_entails(KnowledgeBase& kb, Symbol& q)
    {
        std::unordered_map<std::string, unsigned long> count;
        std::unordered_map<std::string, bool> inferred;

        for ( auto& b : kb.symbols() ) {
            inferred[b.first] = false;
        }

        for ( auto& c : kb.clauses() ) {
            ClauseFinder finder;
            c.second->accept(finder);
            count[c.first] = finder.symbols().size();
        }

        std::queue<Symbol> agenda;
//        for ( auto& s : kb ) {
//            agenda.push(s);
//        }

        while ( !agenda.empty() ) {
            auto p = agenda.front();
            agenda.pop();
            if ( p.GetSymbolName() == q.GetSymbolName() )
                return true;

            if ( !inferred[p.GetSymbolName()] ) {
                inferred[p.GetSymbolName()] = false;

//                for ( auto& c: kb ) {
//
//                }
            }
        }

    }
};


}