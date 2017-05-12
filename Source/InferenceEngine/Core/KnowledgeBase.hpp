//
//  KnowledgeBase.hpp
//  iengine
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan on 12/05/2017
//  Copyright (c) 2016 Jacob Milligan. All rights reserved.
//

#pragma once

#include "InferenceEngine/AST/ClauseFinder.hpp"
#include "InferenceEngine/AST/Private/Stringifier.hpp"
#include "InferenceEngine/AST/Sentence.hpp"
#include "InferenceEngine/Parsing/Parser.hpp"
#include "InferenceEngine/Core/Symbol.hpp"

namespace ie {


class KnowledgeBase {
public:
    void tell(const std::vector<ASTNode::Child>& ast);

    std::unordered_map<std::string, bool>& symbols()
    {
        return symbols_;
    }

    std::unordered_map<std::string, const Sentence*>& clauses()
    {
        return clauses_;
    }

private:
    ie::ClauseFinder finder_;
    ie::Stringifier stringifier_;
    std::unordered_map<std::string, bool> symbols_;
    std::unordered_map<std::string, const Sentence*> clauses_;
};


}