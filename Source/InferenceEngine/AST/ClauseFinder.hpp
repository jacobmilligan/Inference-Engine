//
//  ClauseFinder.hpp
//  iengine
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan on 5/05/2017
//  Copyright (c) 2016 Jacob Milligan. All rights reserved.
//

#pragma once

#include "InferenceEngine/AST/ASTVisitor.hpp"
#include <stack>

namespace ie {

/// @brief ClauseFinder finds complex sentences and atomics and places
/// them into separate containers for iteration
class ClauseFinder : public ASTVisitor {
public:
    /// @brief Visits a sentence - does nothing
    /// @param sentence Sentence to visit
    bool visit(const Sentence& sentence) override;

    /// @brief Visits an atomic and if it's not already discovered, places it
    /// into the symbol container
    /// @param atom The atomic to visit
    bool visit(const AtomicSentence& atom) override;

    /// @brief Visits a complex sentence and adds it to the rules container
    /// @param complex Complex sentence to visit
    bool visit(const ComplexSentence& complex) override;

    /// @brief Gets the container of rules
    /// @return Rules container
    const std::vector<const ComplexSentence*>& rules() const;

    /// @brief Gets all symbols found by the clause finder
    /// @return The symbols container
    const std::vector<std::string>& symbols() const;

    const std::vector<const AtomicSentence*> facts() const;

    const std::vector<std::string>& positive_atomics() const;

    void clear();


    const std::stack<TokenType> connectives() const;

private:
    std::vector<const ComplexSentence*> rules_;
    std::vector<const AtomicSentence*> facts_;
    std::vector<std::string> atomics_;
    std::stack<TokenType> connectives_;
    std::vector<std::string> positive_atomics_;

};


}