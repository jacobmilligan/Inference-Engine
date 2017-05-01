//
//  Parser.hpp
//  InferenceEngine
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan on 29/04/2017
//  Copyright (c) 2016 Jacob Milligan. All rights reserved.
//

#pragma once

#include "InferenceEngine/AST/ASTNode.hpp"

#include <Path/Path.hpp>

namespace ie {


class Parser {
public:
    void parse(const sky::Path& filepath);

    std::vector<ASTNode::Child>& ast();
private:
    std::vector<ASTNode::Child> ast_;
    uint32_t min_precedence_;

    std::string slurp(const std::string& path);

    bool is_atomic(const Token& cur);
    bool is_binary(const TokenType type);
    bool is_unary(const Token& tok);
    bool is_terminal(const TokenType type);

    ASTNode::Child parse_sentence(Lexer::Iterator& iter);
    ASTNode::Child parse_atomic(Lexer::Iterator& iter);
    ASTNode::Child parse_complex_sentence(Lexer::Iterator& iter);
    ASTNode::Child parse_negation(Lexer::Iterator& iter);
};


}