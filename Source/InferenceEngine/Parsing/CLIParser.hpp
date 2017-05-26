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


struct CLIArgument {
    CLIArgument(const std::string& argname, const std::string& desc)
        : name(argname), description(desc)
    {}

    std::string name;
    std::string description;
    std::string value;
};

class CLIParser {
public:
    CLIParser(const std::string& app_name, const char* description);

    void parse(int argc, char** argv);

    void add_positional(const CLIArgument& arg);

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