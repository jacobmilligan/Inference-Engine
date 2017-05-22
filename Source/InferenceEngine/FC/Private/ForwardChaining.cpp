//
//  ForwardChaining.cpp
//  iengine
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan on 12/05/2017
//  Copyright (c) 2016 Jacob Milligan. All rights reserved.
//

#include "InferenceEngine/FC/ForwardChaining.hpp"

namespace ie {


ChainingResult FC::fc_entails(const KnowledgeBase& kb, const Symbol& q) const
{
    ChainingResult result;

    // Table where count[c] is the number of symbols in c's premise
    std::unordered_map<std::string, unsigned long> count;
    // Table with inferred[s] is initially false for all symbols
    std::unordered_map<std::string, bool> inferred;

    for ( auto& b : kb.symbols() ) {
        inferred[b.first] = false;
    }

    for ( auto& c : kb.rules() ) {
        ClauseFinder finder;
        if ( c.second->connective() == TokenType::implication ) {
            c.second->left()->accept(finder);
        } else {
            c.second->accept(finder);
        }
        count[c.first] = finder.symbols().size();
    }

    // List of symbols known to be true in KB
    std::queue<std::string> agenda;
    for ( auto& f : kb.facts() ) {
        agenda.push(f.second->get_value());
    }

    ClauseFinder finder;
    while ( !agenda.empty() ) {
        // Get next symbol in agenda
        auto p = agenda.front();
        agenda.pop();

        // Check if at the end - if so add it to the path and return
        if ( p == q.GetSymbolName() ) {
            result.path.push_back(p);
            result.value = true;
            return result;
        }

        // Check if haven't already inferred p and infer it
        if ( !inferred[p] ) {
            result.path.push_back(p); // add current to the path
            inferred[p] = true; // make inferred

            // For each clause in KB where p is in the premise of c
            for ( auto& c: kb.as_sentence() ) {
                finder.clear();
                c.second->accept(finder); // check if c is in the premise

                auto found = std::find(finder.symbols().begin(),
                                       finder.symbols().end(),
                                       p) != finder.symbols().end();
                // Found the symbol, so decrement the count
                if ( found ) {
                    count[c.first] -= 1;
                    if ( count[c.first] <= 0 ) {
                        // Count less than zero so we've inferred all symbols
                        // in c's premise and can add all the symbols in its
                        // conclusion to the agenda
                        finder.clear();
                        auto complex = as_complex(c.second);
                        complex->right()->accept(finder);
                        for ( auto& s : finder.symbols() ) {
                            agenda.push(s);
                        }
                    }
                }
            }
        }
    }

    result.value = false;
    return result;
}

}