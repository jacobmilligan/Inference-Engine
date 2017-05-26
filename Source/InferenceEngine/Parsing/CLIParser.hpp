//
//  CLIParser.hpp
//  InferenceEngine
//
//  --------------------------------------------------------------
//
//  Authors:       Jacob Milligan & Cormac Collins
//  Student ID:    100660682 & 100655400
//  Unit:          COS30019 - Introduction To AI
//  Program:       Assignment 2 - Inference Engine
//  Date:          29/04/2017
//

#pragma once

#include <string>
#include <vector>

namespace ie {

/// @brief CLIArgument is an argument to give to the CLI parser
struct CLIArgument {
    CLIArgument(const std::string& argname, const std::string& desc)
        : name(argname), description(desc)
    {}

    std::string name;
    std::string description;
    std::string value;
};

/// @brief CLIParser parses given arguments producing a helpful error message
/// with the -h flag
class CLIParser {
public:
    /// @brief Initializes the parser with the app name and description
    /// @param app_name Name to display in help message
    /// @param description Description to display alongside the help message
    CLIParser(const std::string& app_name, const char* description);

    /// @brief Parses the command line and produces results
    /// @param argc
    /// @param argv
    void parse(int argc, char** argv);

    /// @brief Adds a positional argument to the CLI in the order it was added
    /// @param arg argument to add
    void add_positional(const CLIArgument& arg);

    /// @brief Gets the result of a positional argument after parsing the
    /// command line
    /// @param arg_name The name of the argument to get
    /// @return The arguments string result
    std::string get_positional_result(const char* arg_name);

    void reset();

    std::string help_string();

private:
    std::string description_;
    std::string app_name_;

    std::vector<CLIArgument> args_;

    void print_help();
    void print_error(const std::string& err);
};


}