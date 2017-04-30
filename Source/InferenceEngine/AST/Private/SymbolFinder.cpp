//
//  SymbolFinder.cpp
//  iengine
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan on 30/04/2017
//  Copyright (c) 2016 Jacob Milligan. All rights reserved.
//

#include "InferenceEngine/AST/SymbolFinder.hpp"

namespace ie {


void SymbolFinder::visit(const Sentence& sentence)
{
    sentence.accept(*this);
}

void SymbolFinder::visit(const AtomicSentence& atom)
{
    symbols_.push_back(atom.get_value());
}

}