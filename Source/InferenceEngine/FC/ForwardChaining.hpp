//
//  ForwardChaining.hpp
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

#include "InferenceEngine/Core/Symbol.hpp"
#include "InferenceEngine/Core/KnowledgeBase.hpp"

#include <vector>
#include <queue>
#include <unordered_map>

namespace ie {

/// @brief ChainingResult wraps a result from the FC method with a boolean
/// result and a path taken for inference
struct ChainingResult {
    ChainingResult()
        : value(false)
    {}

    bool value;
    std::vector<std::string> path;
};

class FC {
public:
    /// @brief Checks if KB entails q according to the Forward Chaining
    /// inference method
    /// @param kb The knowledge base to check
    /// @param q The query - a propositional symbol
    /// @return The result
    ChainingResult fc_entails(const KnowledgeBase& kb, const Symbol& q) const;

    /// @brief Gets a sentence as a complex sentence
    /// @param sentence The sentence to get
    /// @return Sentence as a complex sentence
    inline const ComplexSentence* as_complex(const Sentence* sentence) const
    {
        return dynamic_cast<const ComplexSentence*>(sentence);
    }

    /// @brief Gets a sentence as an atomic sentence
    /// @param sentence The sentence to get
    /// @return Sentence as a atomic sentence
    inline const AtomicSentence* as_atomic(const Sentence* sentence) const
    {
        return dynamic_cast<const AtomicSentence*>(sentence);
    }

    /// @brief The path taken by the algorithm so far
    /// @return The path
    inline const std::vector<std::string>& path() const
    {
        return path_;
    }

private:
    std::vector<std::string> path_;
};


}