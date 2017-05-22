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

    std::unordered_map<std::string, unsigned long> count;
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

    std::queue<std::string> agenda;
    for ( auto& f : kb.facts() ) {
        agenda.push(f.second->get_value());
    }

    ClauseFinder finder;
    while ( !agenda.empty() ) {
        auto p = agenda.front();
        agenda.pop();

        if ( p == q.GetSymbolName() ) {
            result.path.push_back(p);
            result.value = true;
            return result;
        }

        if ( !inferred[p] ) {
            result.path.push_back(p);
            inferred[p] = true;

            for ( auto& c: kb.rules() ) {
                finder.clear();
                if ( c.second->left() != nullptr ) {
                    c.second->left()->accept(finder);
                } else {
                    c.second->accept(finder);
                }

                auto found = std::find(finder.symbols().begin(),
                                       finder.symbols().end(),
                                       p) != finder.symbols().end();
                if ( found ) {
                    count[c.first] -= 1;
                    if ( count[c.first] <= 0 ) {
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