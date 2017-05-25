//
//  CLIParser.cpp
//  InferenceEngine
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan on 29/04/2017
//  Copyright (c) 2016 Jacob Milligan. All rights reserved.
//

#include "InferenceEngine/Parsing/CLIParser.hpp"

#include <sstream>
#include <iostream>
#include <cstring>

namespace ie {


CLIParser::CLIParser(const std::string& app_name, const char* description)
    : app_name_(app_name), description_(description)
{}


void CLIParser::parse(int argc, char** argv)
{
    for ( int i = 1; i < argc; ++i ) {
        if ( strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0 ) {
            print_help();
            exit(0);
        }

        if ( i - 1 < args_.size() )
            args_[i - 1].value = argv[i];
    }

    if ( argc - 1 < args_.size() ) {
        std::string error = "Incorrect number of arguments.\nExpected ";
        for ( auto& arg : args_ ) {
            error += "<" + arg.name + "> ";
        }
        error.pop_back();
        print_error(error);
        exit(0);
    }
}

void CLIParser::add_positional(const CLIArgument& arg)
{
    args_.push_back(arg);
}

void CLIParser::print_help()
{
    std::cout << help_string() << "\n";
}

std::string CLIParser::get_positional_result(const char* arg_name)
{
    std::string result = "NO RESULTS";

    for ( auto& arg : args_ ) {
        if ( arg.name == arg_name ) {
            result = arg.value;
            break;
        }
    }

    return result;
}

void CLIParser::reset()
{
    for ( auto& arg : args_ ) {
        arg.value = "";
    }
}

std::string CLIParser::help_string()
{
    std::stringstream ss;
    ss << "usage: " << app_name_ << " [-h | --help] ";
    for ( auto& arg : args_ ) {
        ss << "<" << arg.name << "> ";
    }

    ss << "\n" << description_;

    return ss.str();
}

void CLIParser::print_error(const std::string& err)
{
    std::cout << app_name_ << ": " << err << ". See '"
              << app_name_ << " --help'" << std::endl;
}


}
