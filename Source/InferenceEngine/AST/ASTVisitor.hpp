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

/// @brief ASTVisitor is an abstract visitor for visiting the AST produced
/// the parser
class ASTVisitor {
public:
    /// @brief abstract method for visiting a sentence node
    /// @param sentence The sentence node to visit
    /// @return Optional boolean return value
    virtual bool visit(const Sentence& sentence) = 0;
    /// @brief abstract method for visiting a AtomicSentence node
    /// @param atom The AtomicSentence node to visit
    /// @return Optional boolean return value
    virtual bool visit(const AtomicSentence& atom) = 0;
    /// @brief abstract method for visiting a ComplexSentence node
    /// @param complex The ComplexSentence node to visit
    /// @return Optional boolean return value
    virtual bool visit(const ComplexSentence& complex) = 0;
};


}