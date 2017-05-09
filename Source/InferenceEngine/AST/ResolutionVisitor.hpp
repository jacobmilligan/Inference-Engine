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
    bool visit(const Sentence& sentence) override;

    bool visit(const AtomicSentence& atom) override;

    bool visit(const ComplexSentence& complex) override;

    std::vector<std::string> GetSymbols();

    bool calculate(TokenType logic_operator, bool res1, bool res2);

    //Public call to return overall results
    bool GetSolution(std::map<std::string, bool>& modal, const ComplexSentence& complex);

private:

    std::map<std::string, bool> symbol_values_;

    std::vector<std::string> symbols_;

    bool solve(Token tok);

};


}