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


class ResolutionVisitor : public ASTVisitor {
public:
    ResolutionVisitor() {}

    bool visit(const Sentence& sentence) override;

    bool visit(const AtomicSentence& atom) override;

    bool visit(const ComplexSentence& complex) override;

    std::vector<std::string> get_symbols();

    std::unordered_map<std::string, bool> get_symbols_map();

    //calculates result of operator on left or right value
    //If only lVal then it will be the negation operator and will calculate
    bool calculate(TokenType logic_operator, bool lVal, bool rVal);

    //Public call to return overall results
    bool get_solution(const std::unordered_map<std::string, bool>& modal, const Sentence& complex);

    //Public call to return overall results
    bool get_solution(const std::unordered_map<std::string, bool>& modal, const ComplexSentence& complex);

    //get solution atomic version
    bool get_solution(const std::unordered_map<std::string, bool>& modal, const AtomicSentence& atomic);

    std::unordered_map<std::string, bool> symbol_values_;

private:
    std::vector<std::string> symbols_;

    bool solve(Token tok);



};


}