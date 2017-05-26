//
//  Symbol.hpp
//  iengine
//
//  --------------------------------------------------------------
//
//  Authors:       Jacob Milligan & Cormac Collins
//  Student ID:    100660682 & 100655400
//  Unit:          COS30019 - Introduction To AI
//  Program:       Assignment 2 - Inference Engine
//  Date:          05/05/2017
//

#pragma once

#include <string>

namespace ie {

/// @brief Symbol is a single propositional symbol with a boolean value
/// associated with it
class Symbol {
public:
    /// @brief Initializes the symbol with default values
    Symbol();
    /// @brief Initializes the symbol with the given values
    /// @param s The string representation of the symbol
    /// @param val The symbols boolean value
    Symbol(std::string s, bool val) : symbolName_ (s), value_(val) {};

    /// @brief Gets the symbols boolean value
    /// @return The symbols boolean value
    bool value() const;

    /// @brief Gets the symbols string representation
    /// @return The symbols string representation
    std::string name() const;
private:
    std::string symbolName_;
    bool value_ = false;
};


}
