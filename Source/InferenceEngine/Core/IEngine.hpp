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

namespace ie {


class IEngine {
public:
    IEngine()
    {}

    void infer(const std::string& method_str, const sky::Path& filepath);

private:
    KnowledgeBase kb_;
    Parser parser_;
    ClauseFinder finder_;

    InferenceMethod get_method(const std::string& method_str);
};


}