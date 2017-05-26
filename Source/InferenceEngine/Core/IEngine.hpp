//
//  IEngine.hpp
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