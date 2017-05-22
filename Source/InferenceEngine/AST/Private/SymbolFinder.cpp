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

#include <tic.h>
#include "InferenceEngine/AST/SymbolFinder.hpp"

namespace ie {


bool SymbolFinder::visit(const Sentence& sentence)
{
    return sentence.accept(*this);
}

bool SymbolFinder::visit(const AtomicSentence& atom)
{
    auto contains = std::find(symbols_.begin(), symbols_.end(), atom.get_value());
    if ( contains == symbols_.end() ) {
        symbols_.push_back(atom.get_value());
    }

    return true;
}

bool SymbolFinder::visit(const ComplexSentence& complex) {

    if ( complex.left() != nullptr ) {
        complex.left()->accept(*this);
    }
    complex.right()->accept(*this);
    return false;
}


std::vector<std::string> SymbolFinder::get_symbols() const {
    return symbols_;
}


}