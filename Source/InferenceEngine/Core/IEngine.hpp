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

/// @brief IEngine is an inference engine able to be told and asked information
/// via a file input using propositional logic
class IEngine {
public:
    /// @brief Infers the TELL and ASK statement given in the file using
    /// the given inference method
    /// @param method_str String representation of the inference method to use
    /// @param filepath Path to the file to infer
    void infer(const std::string& method_str, const sky::Path& filepath);
private:
    KnowledgeBase kb_;
    Parser parser_;
    ClauseFinder finder_;

    /// @brief Gets a method enum for a string
    /// @param method_str String representation of the method to use
    /// @return Inference method enum representation
    InferenceMethod get_method(const std::string& method_str);
};


}