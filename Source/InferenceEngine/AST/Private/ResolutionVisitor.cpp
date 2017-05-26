//
//  ResolutionVisitor.cpp
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

#include "InferenceEngine/AST/ResolutionVisitor.hpp"

#include <iostream>

namespace ie {

bool ResolutionVisitor::visit(const Sentence& sentence)
{
    sentence.accept(*this);
}

bool ResolutionVisitor::visit(const AtomicSentence& atom)
{
    return solve(atom.get_token());
}

bool ResolutionVisitor::visit(const ComplexSentence& complex) {
    TokenType logic_operator = complex.connective();
    bool res1 = complex.right()->accept(*this);
    bool res2;

    //can be no right side symbol in case of negation
    if(complex.left() != nullptr) {
        res2 = complex.left()->accept(*this);
    }

    return calculate(logic_operator, res2, res1);
}

bool ResolutionVisitor::calculate(TokenType logic_operator, bool lVal, bool rVal){

    switch (logic_operator){
        //Must be at the top because if negation then rVal has not been calculated
        case TokenType ::negation: return !rVal;
        case TokenType ::conjunction: return lVal && rVal;
        case TokenType ::disjunction: return lVal || rVal;
        case TokenType ::implication:
            // A => B |  Truth table - full and complete truth-table options for brevity
            if(lVal && rVal){
                return true;
            }
            else if(!lVal && !rVal){
                return true;
            }
            else if(lVal && !rVal){
                return false;
            }
            else if(!lVal && rVal){
                return true;
            }

        default:
            std::cerr << "Error with operator calculation " << std::endl;
            break;
    }
}

std::vector<std::string> ResolutionVisitor::get_symbols() {
    return symbols_;
}

//Return result value for symbol name
bool ResolutionVisitor::solve(Token tok) {
    return symbol_values_[tok.literal];
}

bool ResolutionVisitor::get_solution(const std::unordered_map<std::string, bool>& modal, const Sentence& complex) {
    symbol_values_ = modal;
    return complex.accept(*this);
}

bool ResolutionVisitor::get_solution(const std::unordered_map<std::string, bool>& modal, const ComplexSentence& complex) {
    symbol_values_ = modal;
    return complex.accept(*this);
}

bool ResolutionVisitor::get_solution(const std::unordered_map<std::string, bool>& modal, const AtomicSentence& atomic) {
    symbol_values_ = modal;
    return atomic.accept(*this);
}

std::unordered_map<std::string, bool> ResolutionVisitor::get_symbols_map() {
    return symbol_values_;
}



}