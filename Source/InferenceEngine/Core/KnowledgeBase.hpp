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

enum class InferenceMethod {
    TT,
    FC,
    BC,
    unknown
};

class KnowledgeBase {
public:
    void tell(const std::vector<ASTNode::Child>& ast);
    void ask(const InferenceMethod method, const Symbol& q);

    inline void clear()
    {
        finder_.clear();
        stringifier_.clear();
        symbols_.clear();
        rules_.clear();
        facts_.clear();
    }

    const std::unordered_map<std::string, bool>& symbols() const
    {
        return symbols_;
    }

    const std::unordered_map<std::string, const ComplexSentence*>& rules() const
    {
        return rules_;
    }

    const std::unordered_map<std::string, const AtomicSentence*>& facts() const
    {
        return facts_;
    }

private:
    ClauseFinder finder_;
    Stringifier stringifier_;
    std::unordered_map<std::string, bool> symbols_;
    std::unordered_map<std::string, const ComplexSentence*> rules_;
    std::unordered_map<std::string, const AtomicSentence*> facts_;
};


}