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
}

void SymbolFinder::visit(const AtomicSentence& atom)
{
    if(AcceptableSymbol(atom)) {
        symbols_.push_back(atom.get_value());
    }
}

void SymbolFinder::visit(const ComplexSentence& complex) {
    complex.right()->accept(*this);
    if(complex.left() != NULL) {
        complex.left()->accept(*this);
    }
}

std::vector<std::string> SymbolFinder::GetSymbols() {
    return symbols_;
}

bool SymbolFinder::AcceptableSymbol(const AtomicSentence& atom) {
    std::string val = atom.get_value();

    if(val == ";" || val == "=>" || val == "!" || val == "&" || val == "|"){
        return false;
    }

    for(auto& sym : symbols_){
        if(val == sym){
            return false;
        }
    }
    return true;
}

}