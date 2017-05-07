//
//  AST.hpp
//  iengine
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan on 30/04/2017
//  Copyright (c) 2016 Jacob Milligan. All rights reserved.
//

#pragma once

#include "InferenceEngine/Parsing/Private/Lexer.hpp"

namespace ie {

class ASTVisitor;

class ASTNode {
public:
    using Child = std::unique_ptr<ASTNode>;
    virtual bool accept(ASTVisitor& visitor) const = 0;
};




}