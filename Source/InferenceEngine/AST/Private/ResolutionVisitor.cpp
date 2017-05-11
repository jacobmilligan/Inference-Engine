//
//  ResolutionVisitor.cpp
//  iengine
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan on 30/04/2017
//  Copyright (c) 2016 Jacob Milligan. All rights reserved.
//

#include <iostream>
#include "InferenceEngine/AST/ResolutionVisitor.hpp"

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

    if(typeid(ComplexSentence) == typeid(AtomicSentence)){
        return visit(complex);
    }
    else{
        TokenType logic_operator = complex.connective();
        bool res1 = complex.right()->accept(*this);
        bool res2;

        //can be no right side symbol in case of negation
        if(complex.left() != nullptr) {
            res2 = complex.left()->accept(*this);
        }

        return calculate(logic_operator, res2, res1);
    }
}

bool ResolutionVisitor::calculate(TokenType logic_operator, bool res1, bool res2){

    switch (logic_operator){
        //Must be at the top because if negation then res2 has not been calculated
        case TokenType ::negation: return !res1;
        case TokenType ::conjunction: return res1 && res2;
        case TokenType ::disjunction: return res1 || res2;
        case TokenType ::implication:
            // A => B |  Truth table - full and complete truth-table options for brevity
            if(res1 && res2){
                return true;
            }
            else if(!res1 && !res2){
                return true;
            }
            else if(res1 && !res2){
                return false;
            }
            else if(!res1 && res2){
                return true;
            }

        default:
        std::cerr << "Error with operator calculation " << std::endl;
            break;
    }
}

std::vector<std::string>& ResolutionVisitor::GetSymbols() {
    return symbols_;
}

//Return result value for symbol name
bool ResolutionVisitor::solve(Token tok) {
    return symbol_values_[tok.literal];
}

bool ResolutionVisitor::GetSolution(std::map<std::string, bool>& model, const ComplexSentence& complex) {

   symbol_values_ = model;


    return complex.accept(*this);
}

}