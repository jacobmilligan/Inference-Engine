//
//  Sentence.hpp
//  iengine
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan on 30/04/2017
//  Copyright (c) 2016 Jacob Milligan. All rights reserved.
//

#pragma once

#include "InferenceEngine/AST/ASTNode.hpp"

namespace ie {

class ASTVisitor;

class Sentence : public ASTNode {
public:
    bool is_root;

    Sentence()
        : is_root(false)
    {}

    bool accept(ASTVisitor& visitor) const override;
};

class AtomicSentence : public Sentence {
public:
    AtomicSentence(const Token& token);
    bool accept(ASTVisitor& visitor) const override;

    std::string get_value() const;
    Token get_token() const;
private:
    Token token_;
};

class ComplexSentence : public Sentence {
public:
    ComplexSentence(ASTNode::Child&& left, const TokenType connective,
                    ASTNode::Child&& right);
    bool accept(ASTVisitor& visitor) const override;

    ASTNode* left() const;
    ASTNode* right() const;
    TokenType connective() const;
private:
    TokenType connective_;
    Child left_;
    Child right_;
};


}