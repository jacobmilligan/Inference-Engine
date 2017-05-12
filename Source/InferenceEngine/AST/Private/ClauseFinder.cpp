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

#include "InferenceEngine/AST/ClauseFinder.hpp"

#include <iostream>

namespace ie {


bool ClauseFinder::visit(const Sentence& sentence)
{
    return true;
}

bool ClauseFinder::visit(const AtomicSentence& atom)
{
    auto contains = std::find(atomics_.begin(), atomics_.end(), atom.get_value());
    if ( contains == atomics_.end() ) {
        atomics_.push_back(atom.get_value());
    }

    bool is_added = false;
    for ( auto& r : rules_ ) {
        auto as_atom = dynamic_cast<const AtomicSentence*>(r);
        if ( as_atom != nullptr && as_atom->get_value() == atom.get_value() ) {
            is_added = true;
            break;
        }
    }

    if ( atom.is_root && !is_added )
        rules_.push_back(&atom);
    return true;
}

bool ClauseFinder::visit(const ComplexSentence& complex)
{
    if ( complex.is_root )
        rules_.push_back(&complex);

    if ( complex.left() != nullptr ) {
        complex.left()->accept(*this);
    }
    complex.right()->accept(*this);

    return true;
}

const std::vector<const Sentence*>& ClauseFinder::rules() const
{
    return rules_;
}

const std::vector<std::string>& ClauseFinder::symbols() const
{
    return atomics_;
}


}