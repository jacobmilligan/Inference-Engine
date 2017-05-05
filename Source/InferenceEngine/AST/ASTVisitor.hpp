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
    virtual bool visit(const Sentence& sentence) = 0;
    virtual bool visit(const AtomicSentence& atom) = 0;
    virtual bool visit(const ComplexSentence& complex) = 0;
};


}