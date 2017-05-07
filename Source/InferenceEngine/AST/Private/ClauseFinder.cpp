//
//  ClauseFinder.cpp
//  iengine
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan on 5/05/2017
//  Copyright (c) 2016 Jacob Milligan. All rights reserved.
//

#include <iostream>
#include "InferenceEngine/AST/ClauseFinder.hpp"

namespace ie {


void ClauseFinder::visit(const Sentence& sentence)
{
}

void ClauseFinder::visit(const AtomicSentence& atom)
{
    auto contains = std::find(atomics_.begin(), atomics_.end(), atom.get_value());
    if ( contains == atomics_.end() ) {
        atomics_.push_back(atom.get_value());
    }
}

void ClauseFinder::visit(const ComplexSentence& complex)
{
    rules_.push_back(&complex);
}

const std::vector<const ComplexSentence*>& ClauseFinder::rules() const
{
    return rules_;
}

const std::vector<std::string>& ClauseFinder::symbols() const
{
    return atomics_;
}


}