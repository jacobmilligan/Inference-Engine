//
//  SymbolFinder.hpp
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

namespace ie {


    class SymbolFinder : public ASTVisitor {
public:
    void visit(const Sentence& sentence) override;

    void visit(const AtomicSentence& atom) override;

    void visit(const ComplexSentence& complex) override;

    std::vector<std::string> GetSymbols();

private:
    std::vector<std::string> symbols_;

    bool AcceptableSymbol(const AtomicSentence& atom);
};


}