//
//  ASTVisitor.hpp
//  iengine
//
//  --------------------------------------------------------------
//
//  Authors:       Jacob Milligan & Cormac Collins
//  Student ID:    100660682 & 100655400
//  Unit:          COS30019 - Introduction To AI
//  Program:       Assignment 2 - Inference Engine
//  Date:          30/04/2017
//

#pragma once

#include "InferenceEngine/AST/Sentence.hpp"

namespace ie {

class Sentence;

class ASTVisitor {
public:
    virtual bool visit(const Sentence& sentence) = 0;
    virtual bool visit(const AtomicSentence& atom) = 0;
    virtual bool visit(const ComplexSentence& complex) = 0;
};


}