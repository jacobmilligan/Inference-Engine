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

void ResolutionVisitor::visit(const Sentence& sentence)
{
    sentence.accept(*this);
}

void ResolutionVisitor::visit(const AtomicSentence& atom)
{
    _tokenFIFO.push(atom.get_value());
}

void ResolutionVisitor::visit(const ComplexSentence& complex) {

    if(typeid(ComplexSentence) == typeid(AtomicSentence)){
        visit_return(complex);
    }
    else{
        //What can it be?
        if(!complex.connective()){
            complex.accept(*this);
        }
        else if(complex.connective() == TokenType::conjunction){
            _tokenFIFO.push("&");
        }
        else if(complex.connective() == TokenType::disjunction){
            _tokenFIFO.push("|");
        }
        else if (complex.connective() == TokenType::implication){
            _tokenFIFO.push("=>");
        }
        else if (complex.connective() == TokenType::negation){
            _tokenFIFO.push("!");
        }

        complex.accept(*this);
    }
}

std::vector<std::string> ResolutionVisitor::GetSymbols() {
    return symbols_;
}

bool ResolutionVisitor::visit_return(const ComplexSentence& complex) {
    if(typeid(ComplexSentence) == typeid(AtomicSentence)){
        visit_return(complex);
    }
    else{
        if(complex.connective() == TokenType::conjunction||
                complex.connective() == TokenType::disjunction ||
                complex.connective() == TokenType::implication ||
                complex.connective() == TokenType::negation){

            _tokenFIFO.push(complex.connective());
            complex.accept(*this);
        }


    }


}

bool ResolutionVisitor::visit_return(const AtomicSentence& atom) {
    return solve(atom.get_token());
}

bool ResolutionVisitor::visit_return(const Sentence& sentence) {
    }

void ResolutionVisitor::AddSymbolValues(std::vector<Symbol *> sym) {
    truthTableSymbolList_ = sym;
}

bool ResolutionVisitor::calculateStack(std::stack<std::string> stack){

    std::string& sym = stack.top();
    stack.pop();




    if(sym == "!"){
        sym = stack.top();
        stack.pop();
        while(!isOperator(sym)){

        }
    }
    else if (sym == "&"){

    }
    else if (sym == "=>"){

    }
    else if (sym == "|"){

    }

}

bool ResolutionVisitor::solve(Token tok) {

    for (auto *sym : truthTableSymbolList_) {
        if (sym->GetSymbolName() == tok.literal) {
            return sym->GetValue();
        }
    }
    std::cerr << "Symbol list error" << std::endl;

}

bool ResolutionVisitor::GetSolution(const ComplexSentence& complex) {
    complex.accept(*this);

    calc

}

bool isOperator(std::string sym){
    return ((sym == "!") || (sym == "&")
            || (sym == "=>") || (sym == "|"));
}

}