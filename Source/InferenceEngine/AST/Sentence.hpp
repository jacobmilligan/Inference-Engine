//
//  Sentence.hpp
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