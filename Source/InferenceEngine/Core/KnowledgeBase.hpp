//
//  KnowledgeBase.hpp
//  iengine
//
//  --------------------------------------------------------------
//
//  Authors:       Jacob Milligan & Cormac Collins
//  Student ID:    100660682 & 100655400
//  Unit:          COS30019 - Introduction To AI
//  Program:       Assignment 2 - Inference Engine
//  Date:          12/05/2017
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

    const std::unordered_map<std::string, const Sentence*> as_sentence() const
    {
        std::unordered_map<std::string, const Sentence*> result;
        for ( auto& r : rules_ ) {
            auto as_sentence = dynamic_cast<const Sentence*>(r.second);
            result.emplace(r.first, as_sentence);
        }
        for ( auto& f : facts_ ) {
            auto as_sentence = dynamic_cast<const Sentence*>(f.second);
            result.emplace(f.first, as_sentence);
        }
        return result;
    };

private:
    ClauseFinder finder_;
    Stringifier stringifier_;
    std::unordered_map<std::string, bool> symbols_;
    std::unordered_map<std::string, const ComplexSentence*> rules_;
    std::unordered_map<std::string, const AtomicSentence*> facts_;
};


}