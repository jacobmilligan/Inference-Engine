//
//  ClauseFinder.cpp
//  iengine
//
//  --------------------------------------------------------------
//
//  Authors:       Jacob Milligan & Cormac Collins
//  Student ID:    100660682 & 100655400
//  Unit:          COS30019 - Introduction To AI
//  Program:       Assignment 2 - Inference Engine
//  Date:          05/05/2017
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
    if ( contains == atomics_.end() )
        atomics_.push_back(atom.get_value());

    bool is_added = false;
    for ( auto& r : facts_ ) {
        if ( r != nullptr && r->get_value() == atom.get_value() ) {
            is_added = true;
            break;
        }
    }

    if ( atom.is_root && !is_added )
        facts_.push_back(&atom);
    return true;
}

bool ClauseFinder::visit(const ComplexSentence& complex)
{
    connectives_.push(complex.connective());

    if ( complex.is_root )
        rules_.push_back(&complex);

    if ( complex.left() != nullptr ) {
        complex.left()->accept(*this);
    }
    complex.right()->accept(*this);

    return true;
}

const std::vector<const ComplexSentence*>& ClauseFinder::rules() const
{
    return rules_;
}

const std::vector<std::string>& ClauseFinder::symbols() const
{
    return atomics_;
}

void ClauseFinder::clear()
{
    rules_.clear();
    atomics_.clear();

    while(!connectives_.empty()) {
        connectives_.pop();
    }
}

const std::vector<const AtomicSentence*> ClauseFinder::facts() const
{
    return facts_;
}

const std::stack<TokenType> ClauseFinder::connectives() const {
    return connectives_;
}


}