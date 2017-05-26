//
//  KnowledgeBase.hpp
//  iengine
//
//  --------------------------------------------------------------
//
//  Authors:       Jacob Milligan & Cormac Collins
//  Student ID:    100660682 & 100655400
//  Unit:          COS30019 - Introduction To AI
//  Program:       Assignment 2 - Inference Engine
//  Date:          12/05/2017
//

#pragma once

#include "InferenceEngine/AST/ClauseFinder.hpp"
#include "InferenceEngine/AST/Private/Stringifier.hpp"
#include "InferenceEngine/AST/Sentence.hpp"
#include "InferenceEngine/Parsing/Parser.hpp"
#include "InferenceEngine/Core/Symbol.hpp"

namespace ie {

enum class InferenceMethod {
    TT,
    FC,
    BC,
    unknown
};

/// @brief KnowledgeBase is a storage for a KB Agents knowledge representation
class KnowledgeBase {
public:
    /// @brief Tells the knowledge base using an AST produced by the result
    /// of parsing a string
    /// @param ast The AST to tell with
    void tell(const std::vector<ASTNode::Child>& ast);

    /// @brief Asks a question of the knowledge base using a given inference
    /// method and a symbol
    /// @param method The method to use to infer q
    /// @param q The symbol to ask the knowledge base
    void ask(const InferenceMethod method, const Symbol& q);

    /// @brief Clears the knowledge bases internal containers
    inline void clear()
    {
        finder_.clear();
        stringifier_.clear();
        symbols_.clear();
        rules_.clear();
        facts_.clear();
    }

    /// @brief Gets all the symbols found in the KB
    /// @return List of symbols
    inline const std::unordered_map<std::string, bool>& symbols() const
    {
        return symbols_;
    }

    /// @brief Gets all the rules in KB
    /// @return list of rules
    inline const std::unordered_map<std::string, const ComplexSentence*>& rules() const
    {
        return rules_;
    }

    /// @brief Gets all facts (atomic sentences told to KB via TELL) in KB
    /// @return The facts in KB
    inline const std::unordered_map<std::string, const AtomicSentence*>& facts() const
    {
        return facts_;
    }

    /// @brief Gets the entire knowledge base as a conjunction of clauses - a
    /// single sentence
    /// @return KB as a sentence
    const std::unordered_map<std::string, const Sentence*> as_sentence() const;

private:
    ClauseFinder finder_;
    Stringifier stringifier_;
    std::unordered_map<std::string, bool> symbols_;
    std::unordered_map<std::string, const ComplexSentence*> rules_;
    std::unordered_map<std::string, const AtomicSentence*> facts_;
};


}