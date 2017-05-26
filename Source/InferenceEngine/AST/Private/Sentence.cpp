//
//  Sentence.cpp
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

#include "InferenceEngine/AST/Sentence.hpp"
#include "InferenceEngine/AST/ASTVisitor.hpp"

namespace ie {


bool Sentence::accept(ASTVisitor& visitor) const
{
    return visitor.visit(*this);
}


bool AtomicSentence::accept(ASTVisitor& visitor) const
{
    return visitor.visit(*this);
}

AtomicSentence::AtomicSentence(const Token& token)
    : token_(token)
{}

std::string AtomicSentence::get_value() const
{
    return token_.literal;
}

Token AtomicSentence::get_token() const {
    return token_;
}


bool ComplexSentence::accept(ASTVisitor& visitor) const
{
    return visitor.visit(*this);
}

ComplexSentence::ComplexSentence(ASTNode::Child&& left, const TokenType connective,
                                 ASTNode::Child&& right)
    : left_(std::move(left)), right_(std::move(right)), connective_(connective)
{}

ASTNode* ComplexSentence::left() const
{
    return left_.get();
}

ASTNode* ComplexSentence::right() const
{
    return right_.get();
}

TokenType ComplexSentence::connective() const
{
    return connective_;
}


}