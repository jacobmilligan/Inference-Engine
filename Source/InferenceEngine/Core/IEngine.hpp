//
//  IEngine.hpp
//  iengine
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan on 30/04/2017
//  Copyright (c) 2016 Jacob Milligan. All rights reserved.
//

#pragma once

#include "InferenceEngine/Parsing/CLIParser.hpp"
#include "InferenceEngine/Core/KnowledgeBase.hpp"

#include <algorithm>
#include <InferenceEngine/AST/SymbolFinder.hpp>

namespace ie {


class IEngine {
public:
    IEngine()
    {}

    void infer(const std::string& method_str, const sky::Path& filepath)
    {
        auto method = get_method(method_str);
        if ( method == InferenceMethod::unknown ) {
            std::cout << "IEngine: invalid inference method '"
                      << method_str << "'" << std::endl;
            return;
        }

        auto pre = parser_.preprocess(filepath);

        Parser tell;
        tell.parse(pre.tell);
        kb_.tell(tell.ast());

        Parser ask;
        ask.parse(pre.ask);
        parser_.parse(pre.ask);

        parser_.ast()[0]->accept(finder_);

        auto q = Symbol(finder_.symbols()[0], false);

        kb_.ask(method, q);
    }
private:
    KnowledgeBase kb_;
    Parser parser_;
    ClauseFinder finder_;

    InferenceMethod get_method(const std::string& method_str)
    {
        std::string lower = method_str;
        std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
        auto method = InferenceMethod::unknown;

        if ( lower == "tt"  )
            method = InferenceMethod::TT;
        if ( lower == "bc"  )
            method = InferenceMethod::BC;
        if ( lower == "fc"  )
            method = InferenceMethod::FC;

        return method;
    }
};


}