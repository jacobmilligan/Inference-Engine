//
//  ASTVisitor.cpp
//  iengine
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan on 30/04/2017
//  Copyright (c) 2016 Jacob Milligan. All rights reserved.
//

#include "InferenceEngine/AST/ASTVisitor.hpp"
#include "InferenceEngine/AST/Sentence.hpp"

namespace ie {


void ASTVisitor::visit(const Sentence& sentence)
{
    sentence.accept(*this);
}

void ASTVisitor::visit(const AtomicSentence& atom)
{

}


}