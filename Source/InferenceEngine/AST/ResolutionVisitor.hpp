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
#include <map>

namespace ie {


    class ResolutionVisitor : public ASTVisitor {
public:

    bool visit(const Sentence& sentence) override;

    bool visit(const AtomicSentence& atom) override;

    bool visit(const ComplexSentence& complex) override;

    std::vector<std::string> get_symbols();

    std::map<std::string, bool> get_symbols_map();

    //calculates result of operator on left or right value
    //If only lVal then it will be the negation operator and will calculate
    bool calculate(TokenType logic_operator, bool lVal, bool rVal);

    //Public call to return overall results
    bool get_solution(std::map<std::string, bool>& modal, const Sentence& complex);

    //Public call to return overall results
    bool get_solution(std::map<std::string, bool>& modal, const ComplexSentence& complex);

    //get solution atomic version
    bool get_solution(std::map<std::string, bool>& modal, const AtomicSentence& atomic);

    std::map<std::string, bool> symbol_values_;

private:



    std::vector<std::string> symbols_;

    bool solve(Token tok);



};


}