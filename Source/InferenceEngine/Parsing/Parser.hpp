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

    std::string slurp(const std::string& path);

    bool is_binary(const TokenType type);

    ASTNode::Child parse_sentence(Lexer::Iterator& iter, const uint32_t prec);
    ASTNode::Child parse_atomic(Lexer::Iterator& iter);
    ASTNode::Child parse_connective(ASTNode::Child& lhs, const Token& connective,
                                    ASTNode::Child& rhs);
    ASTNode::Child parse_negation(Lexer::Iterator& iter, const uint32_t prec);
};


}