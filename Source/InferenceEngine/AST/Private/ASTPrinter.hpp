//
//  ASTPrinter.hpp
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

#include "InferenceEngine/AST/ASTVisitor.hpp"

#include <iostream>

namespace ie {


class ASTPrinter : public ASTVisitor {
public:
    bool visit(const Sentence& sentence) override
    {
        return true;
    }

    bool visit(const AtomicSentence& atom) override
    {
        std::cout << atom.get_value();
        return true;
    }

    bool visit(const ComplexSentence& complex) override
    {
        std::cout << "(";
        if ( complex.left() != nullptr ) {
            complex.left()->accept(*this);
        }
        std::cout << token_string(complex.connective());
        complex.right()->accept(*this);
        std::cout << ")";
        return true;
    }

private:
    std::string token_string(const TokenType tok)
    {
        switch (tok) {
            case TokenType::negation: return "!";
            case TokenType::conjunction: return "&";
            case TokenType::disjunction: return "|";
            case TokenType::implication: return "=>";
            case TokenType::symbol: return "";
            case TokenType::truth: return "true";
            case TokenType::falsity: return "false";
            case TokenType::tell: return "TELL";
            case TokenType::ask: return "ASK";
            case TokenType::semicolon: return ";";
            case TokenType::lparen: return "(";
            case TokenType::rparen: return ")";
            case TokenType::eof: return "EOF";
            case TokenType::unknown: return "UNKNOWN";
        }
    }
};


}