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

    if ( kb.facts().find(q.GetSymbolName()) != kb.facts().end() )
        return true;

    std::queue<std::string> agenda;
    std::set<std::string> inferred;

    agenda.push(q.GetSymbolName());
    inferred.insert(q.GetSymbolName());

    ClauseFinder finder;
    while ( !agenda.empty() ) {
        auto p = agenda.front();
        agenda.pop();

        path_.push_back(p);

        if ( kb.facts().find(p) != kb.facts().end() && agenda.empty() ) {
            std::reverse(path_.begin(), path_.end());
            return true;
        }

        for ( auto& r : kb.rules() ) {
            finder.clear();
            r.second->right()->accept(finder);
            auto consequence = std::find(finder.symbols().begin(),
                                     finder.symbols().end(),
                                     p) != finder.symbols().end();

            if ( consequence ) {
                finder.clear();
                r.second->left()->accept(finder);

                for ( auto& s : finder.symbols() ) {
                    if ( agenda.empty() && inferred.find(s) != inferred.end() ) {
                        std::reverse(path_.begin(), path_.end());
                        return true;
                    }

                    if ( inferred.find(s) == inferred.end() ) {
                        agenda.push(s);
                        inferred.insert(p);
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