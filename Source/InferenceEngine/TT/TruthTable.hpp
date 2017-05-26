//
//  TruthTable.hpp
//  iengine
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

#include "InferenceEngine/AST/ClauseFinder.hpp"
#include "InferenceEngine/Core/KnowledgeBase.hpp"
#include "InferenceEngine/Core/Symbol.hpp"
#include "Model.hpp"

#include <vector>
#include <unordered_map>

namespace ie {

/// @brief Response is a response from a truth tables ASK method containing
/// the result and number of models inferred in the truth table as true
class Response {
public:
    bool result = false;
    int models_inferred = 0;
    Response(int mods, bool res)
        : models_inferred(mods), result(res)
    {};
};

/// @brief TruthTable encapsulates the model enumeration inference method that
/// builds a truth table, inferring the number of rows in which a particular
/// question, alpha, satisfies the knowledge base
class TruthTable {
private:
    int models_; ///< number of models inferred so far

    /// @brief Builds a truth table and enumerates all models recursively.
    /// For reference, see pp. 248 of Artificial Intelligence: A Modern Approach
    /// @param kb The knowledge base to check
    /// @param alpha The symbol to check for
    /// @param symbols The valid symbols in the current iteration
    /// @param model The current partial model
    /// @return True if alpha is valid, false otherwise
    bool tt_check_all(const KnowledgeBase& kb, const Symbol& alpha,
                          std::unordered_map<std::string, bool> symbols,
                          const Model& model);

public:
    /// @brief Initializes the truth table with zero models inferred
    TruthTable()
        : models_(0)
    {}

    /// @brief Asks whether a given symbol is true in the knowledge base using
    /// the model enumeration method to build a truth table, returning the
    /// number of models in which alpha is true and the result
    /// @param kb The knowledge base to ask
    /// @param alpha The symbol to ask
    /// @return True if alpha is valid in KB, false otherwise
    Response ask(const KnowledgeBase& kb, const Symbol& alpha);
};

}
