//
//  Parser.hpp
//  InferenceEngine
//
//  --------------------------------------------------------------
//
//  Authors:       Jacob Milligan & Cormac Collins
//  Student ID:    100660682 & 100655400
//  Unit:          COS30019 - Introduction To AI
//  Program:       Assignment 2 - Inference Engine
//  Date:          29/04/2017
//

#pragma once

#include "InferenceEngine/AST/ASTNode.hpp"

#include <Path/Path.hpp>

namespace ie {


/// @brief PreprocessingResult is a POD struct containing the tell and ask
/// strings without 'TELL' and 'ASK'
struct PreprocessingResult {
    PreprocessingResult(const std::string& tellstr, const std::string& askstr)
        : tell(tellstr), ask(askstr)
    {}

    /// @brief The TELL statement
    const std::string tell;
    /// @brief The ASK statement
    const std::string ask;
};

/// @brief Parser parses a string input of propositional logic and turns it
/// into an abstract syntax tree for traversing
class Parser {
public:
    /// @brief Preprocesses a file and turns it into TELL and ASK strings
    /// @param filepath The absolute path of the file to preprocess
    /// @return The preprocessing POD struct result
    static PreprocessingResult preprocess(const sky::Path& filepath);

    /// @brief Parses a string of propositional logic into an AST
    /// @param str The string to parse
    void parse(const std::string& str);

    /// @brief Gets the AST from the parsed result
    /// @return The parsed strings AST representation
    std::vector<ASTNode::Child>& ast();
private:
    std::vector<ASTNode::Child> ast_;

    static std::string slurp(const std::string& path);

    bool is_binary(const TokenType type);

    ASTNode::Child parse_sentence(Lexer::Iterator& iter, const uint32_t prec);
    ASTNode::Child parse_atomic(Lexer::Iterator& iter);
    ASTNode::Child parse_connective(ASTNode::Child& lhs, const Token& connective,
                                    ASTNode::Child& rhs);
    ASTNode::Child parse_negation(Lexer::Iterator& iter, const uint32_t prec);
};


}