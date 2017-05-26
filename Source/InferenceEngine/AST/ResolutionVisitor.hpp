//
//  ResolutionVisitor.hpp
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
#include "InferenceEngine/Core/KnowledgeBase.hpp"
#include "InferenceEngine/Core/Symbol.hpp"

#include <vector>
#include <unordered_map>

namespace ie {

/// @brief ResolutionVisitor visits the AST of a clause and returns a boolean
/// value indicating its truth value based on the given knowledge base
class ResolutionVisitor : public ASTVisitor {
public:
    /// @brief Initializes the visitor
    ResolutionVisitor() {}

    /// @brief Visits a sentence and solves it
    /// @param sentence The sentence to visit
    /// @return True if KB entails, false otherwise
    bool visit(const Sentence& sentence) override;
    /// @brief Visits an atomic sentence and solves it
    /// @param atom The atomic to visit
    /// @return True if KB entails, false otherwise
    bool visit(const AtomicSentence& atom) override;

    /// @brief Visits a complex sentence and solves it
    /// @param complex The complex sentence to visit
    /// @return True if KB entails, false otherwise
    bool visit(const ComplexSentence& complex) override;

    /// @brief calculates result of operator on left or right value
    /// If only lVal then it will be the negation operator and will calculate
    bool calculate(TokenType logic_operator, bool lVal, bool rVal);

    /// @brief call to return overall results
    bool get_solution(const std::unordered_map<std::string, bool>& model, const Sentence& complex);

    /// @brief The value found of all symbols in the clause
    std::unordered_map<std::string, bool> symbol_values_;

private:
    std::vector<std::string> symbols_;

    bool solve(Token tok);



};


}