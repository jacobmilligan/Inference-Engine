//
//  KnowledgeBase.cpp
//  iengine
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan on 12/05/2017
//  Copyright (c) 2016 Jacob Milligan. All rights reserved.
//

#include "InferenceEngine/AST/ClauseFinder.hpp"
#include "InferenceEngine/Core/KnowledgeBase.hpp"

namespace ie {


void KnowledgeBase::tell(const std::vector<ASTNode::Child>& ast)
{
    for ( auto& s : ast ) {
        s->accept(finder_);
    }

    std::string c = "";
    for ( auto& r : finder_.rules() ) {
        r->accept(stringifier_);
        c = stringifier_.current_string();
        auto found = clauses_.find(c) != clauses_.end();
        if ( !found ) {
            clauses_[c] = dynamic_cast<const Sentence*>(r);
        }
        stringifier_.clear();
    }

    for ( auto& s : finder_.symbols() ) {
        if ( symbols_.find(s) == symbols_.end() ) {
            symbols_[s] = false;
        }
    }
}


}