//
//  ASTPrinter.hpp
//  iengine
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan on 30/04/2017
//  Copyright (c) 2016 Jacob Milligan. All rights reserved.
//

#pragma once

#include "InferenceEngine/AST/ASTVisitor.hpp"

#include <iostream>

namespace ie {


class ASTPrinter : public ASTVisitor {
public:
    void visit(const Sentence& sentence) override
    {
    }

    void visit(const AtomicSentence& atom) override
    {
        std::cout << atom.get_value();
        //push_back(atom.get_value());
    }

    void visit(const ComplexSentence& complex) override
    {
        std::cout << "(";
        if ( complex.left() != nullptr ) {
            complex.left()->accept(*this);
        }
        std::cout << token_string(complex.connective());
        complex.right()->accept(*this);
        std::cout << ")";
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