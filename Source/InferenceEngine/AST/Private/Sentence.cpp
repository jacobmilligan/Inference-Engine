//
//  Sentence.cpp
//  iengine
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan on 30/04/2017
//  Copyright (c) 2016 Jacob Milligan. All rights reserved.
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