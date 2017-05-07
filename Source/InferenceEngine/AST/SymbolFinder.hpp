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
    bool visit(const Sentence& sentence) override;

    bool visit(const AtomicSentence& atom) override;

private:
    std::vector<std::string> symbols_;
};


}