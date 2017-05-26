//
//  AST.hpp
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

#include "InferenceEngine/Parsing/Private/Lexer.hpp"

namespace ie {

class ASTVisitor;

/// @brief ASTNode is a node used in the Abstract Syntax Tree produced by the
/// parser with a single virtual accept() method for accepting a visitor
class ASTNode {
public:
    using Child = std::unique_ptr<ASTNode>;

    /// @brief Abstract method for accepting a visitor
    /// @param visitor The visitor to accept
    /// @return Optional true or false return
    virtual bool accept(ASTVisitor& visitor) const = 0;
};




}