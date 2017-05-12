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
    const ComplexSentence* as_complex(const Sentence* sentence)
    {
        return dynamic_cast<const ComplexSentence*>(sentence);
    }

    const AtomicSentence* as_atomic(const Sentence* sentence)
    {
        return dynamic_cast<const AtomicSentence*>(sentence);
    }

    bool fc_entails(KnowledgeBase& kb, Symbol& q)
    {
        path_.clear();

        std::unordered_map<std::string, unsigned long> count;
        std::unordered_map<std::string, bool> inferred;

        for ( auto& b : kb.symbols() ) {
            inferred[b.first] = false;
        }

        for ( auto& c : kb.rules() ) {
            ClauseFinder finder;
            c.second->accept(finder);
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

            path_.push_back(p);

            if ( p == q.GetSymbolName() )
                return true;

            if ( !inferred[p] ) {
                inferred[p] = true;

                for ( auto& c: kb.rules() ) {
                    finder.clear();
                    c.second->accept(finder);

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
        return false;
    }

    std::vector<std::string>& path()
    {
        return path_;
    }

private:
    std::vector<std::string> path_;
};


}