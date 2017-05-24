//
//  BC.cpp
//  iengine
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan on 24/05/2017
//  Copyright (c) 2016 Jacob Milligan. All rights reserved.
//

#include "InferenceEngine/BC/BC.hpp"

#include <queue>
#include <set>

namespace ie {


bool ie::BC::bc_entails(const KnowledgeBase& kb, const Symbol& q)
{
    path_.clear();

    // Check kb if the query is already a fact before proceeding
    if ( kb.facts().find(q.GetSymbolName()) != kb.facts().end() )
        return true;

    // holds symbols on the left hand side that haven't been inferred
    // or aren't facts
    std::queue<std::string> agenda;
    // All symbols that already have their heads in the agenda
    std::set<std::string> searched;

    agenda.push(q.GetSymbolName());
    searched.insert(q.GetSymbolName());

    ClauseFinder finder;

    while ( !agenda.empty() ) {
        auto p = agenda.front();
        agenda.pop();

        path_.push_back(p);

        // If p is a fact and no more symbols are in the agenda then we've
        // arrived at a terminal node in the search and can safely infer truth
        if ( kb.facts().find(p) != kb.facts().end() && agenda.empty() ) {
            std::reverse(path_.begin(), path_.end());
            return true;
        }

        // Search all rules to see if p occurs in the consequence of any of them
        for ( auto& r : kb.rules() ) {
            finder.clear();
            r.second->right()->accept(finder);
            // Check if p appears as a consequence in the current rule
            auto consequence = std::find(finder.symbols().begin(),
                                     finder.symbols().end(),
                                     p) != finder.symbols().end();

            if ( consequence ) {
                finder.clear();
                // Get all symbols in the lhs
                r.second->left()->accept(finder);

                for ( auto& s : finder.symbols() ) {
                    // If the agenda is empty and s has already been searched
                    // then we can safely say that we've arrived at a terminal
                    // node in the search and therefore an inference and can
                    // return a truth
                    if ( agenda.empty() && searched.find(s) != searched.end() ) {
                        std::reverse(path_.begin(), path_.end());
                        return true;
                    }

                    // If s hasn't been searched already add it to the agenda
                    // and record it as searched
                    if ( searched.find(s) == searched.end() ) {
                        agenda.push(s);
                        searched.insert(p);
                    }
                }
            }
        }
    }

    return false;
}

std::vector<std::string> BC::path()
{
    return path_;
}


}