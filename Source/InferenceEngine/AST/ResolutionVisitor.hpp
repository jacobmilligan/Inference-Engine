//
//  ResolutionVisitor.hpp
//  iengine
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan on 30/04/2017
//  Copyright (c) 2016 Jacob Milligan. All rights reserved.
//

#pragma once

#include "InferenceEngine/AST/ASTVisitor.hpp"

#include <vector>
#include <InferenceEngine/Core/Symbol.hpp>
#include <queue>

namespace ie {


    class ResolutionVisitor : public ASTVisitor {
public:

    // old functions
    void visit(const Sentence& sentence) override;

    void visit(const AtomicSentence& atom) override;

    void visit(const ComplexSentence& complex) override;

    //return type functions
    bool visit_return(const Sentence& sentence);

    bool visit_return(const AtomicSentence& atom);

    bool visit_return(const ComplexSentence& complex);

    std::vector<std::string> GetSymbols();

    //Truth table symbols with actual values
    void AddSymbolValues(std::vector<Symbol*> sym);

    bool calculate(Token a, Token b, Token connective);

    bool GetSolution(const ComplexSentence& complex);

private:

    std::stack<std::string> _tokenFIFO;
    std::vector<Symbol*> truthTableSymbolList_;

    std::vector<std::string> symbols_;

    bool solve(Token tok);

};


}