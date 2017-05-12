//
//  Stringifier.hpp
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


class Stringifier : public ASTVisitor {
public:
    bool visit(const Sentence& sentence) override
    {
        return true;
    }

    bool visit(const AtomicSentence& atom) override
    {
        current_string_ += atom.get_value();
        return true;
    }

    bool visit(const ComplexSentence& complex) override
    {
        if ( complex.left() != nullptr ) {
            complex.left()->accept(*this);
        }
        current_string_ += token_string(complex.connective());
        complex.right()->accept(*this);
        return true;
    }

    void clear()
    {
        current_string_ = "";
    }

    std::string current_string()
    {
        return current_string_;
    }

private:
    std::string current_string_;

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