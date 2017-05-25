//
//  ForwardChaining.hpp
//  iengine
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan on 12/05/2017
//  Copyright (c) 2016 Jacob Milligan. All rights reserved.
//

#pragma once

#include "InferenceEngine/Core/Symbol.hpp"
#include "InferenceEngine/Core/KnowledgeBase.hpp"

#include <vector>
#include <queue>
#include <tuple>
#include <unordered_map>

namespace ie {

struct ChainingResult {
    ChainingResult()
        : value(false)
    {}

    bool value;
    std::vector<std::string> path;
};

class FC {
public:
    ChainingResult fc_entails(const KnowledgeBase& kb, const Symbol& q) const;

    inline const ComplexSentence* as_complex(const Sentence* sentence) const
    {
        return dynamic_cast<const ComplexSentence*>(sentence);
    }

    inline const AtomicSentence* as_atomic(const Sentence* sentence) const
    {
        return dynamic_cast<const AtomicSentence*>(sentence);
    }

    inline const std::vector<std::string>& path() const
    {
        return path_;
    }

private:
    std::vector<std::string> path_;
};


}