//
//  Model.hpp
//  iengine
//
//  --------------------------------------------------------------
//
//  Authors:       Jacob Milligan & Cormac Collins
//  Student ID:    100660682 & 100655400
//  Unit:          COS30019 - Introduction To AI
//  Program:       Assignment 2 - Inference Engine
//  Date:          22/05/2017
//

#pragma once

#include "InferenceEngine/AST/ResolutionVisitor.hpp"

#include <unordered_map>

namespace ie {

/// @brief Model is a class representing a single row in a truth table
class Model {
public:
    /// @brief Checks if a particular symbol is true in the models row
    /// @param symbol The symbol to check
    /// @return True if symbol is true in model, false otherwise
    bool is_true(const std::string& symbol) const;

    /// @brief Checks if a particular group of sentences is true in the models
    /// row as a conjunction of sentences
    /// @param sentences The map of sentences to check
    /// @return True if all sentences are true in model, false otherwise
    bool is_true(const std::unordered_map<std::string, const Sentence*>& sentences) const;

    /// @brief Gets this model as a copy of itself extended to contain the
    /// given symbol assigned as the given value
    /// @param symbol The symbol to extend the model with
    /// @param value The value to assign to the symbol
    /// @return Extended model
    Model extend(const std::string& symbol, const bool value) const;
private:
    std::unordered_map<std::string, bool> values_; ///< the row
};


}