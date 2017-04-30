//
//  ASTVisitor.hpp
//  iengine
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan on 30/04/2017
//  Copyright (c) 2016 Jacob Milligan. All rights reserved.
//

#pragma once

#include "Sentence.hpp"

namespace ie {

class Sentence;

class ASTVisitor {
public:
    virtual void visit(const Sentence& sentence) = 0;
    virtual void visit(const AtomicSentence& atom) = 0;
    virtual void visit(const ComplexSentence& complex) = 0;
};


}