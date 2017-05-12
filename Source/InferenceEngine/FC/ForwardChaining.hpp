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
#include <unordered_map>

namespace ie {


class FC {
public:
    bool fc_entails(KnowledgeBase& kb, Symbol& q);

    inline const ComplexSentence* as_complex(const Sentence* sentence)
    {
        return dynamic_cast<const ComplexSentence*>(sentence);
    }

    inline const AtomicSentence* as_atomic(const Sentence* sentence)
    {
        return dynamic_cast<const AtomicSentence*>(sentence);
    }

    inline std::vector<std::string>& path()
    {
        return path_;
    }

private:
    std::vector<std::string> path_;
};


}