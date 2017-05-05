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
    auto help_flag = false;
    std::string error = "";

    for ( int i = 1; i < argc; ++i ) {
        if ( strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0 ) {
           help_flag = true;
           break;
        }

        if ( i - 1 < args_.size() ) {
            args_[i - 1].value = argv[i];
        } else {
            error = "Incorrect number of arguments. Expected ";
            for ( auto& arg : args_ ) {
                error += "<" + arg.name + "> ";
            }
            break;
        }
    }

    if ( help_flag ) {
        print_help();
        reset();
    }

    if ( error.size() > 0 ) {
        print_error(error);
        reset();
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
              << app_name_ << "--help'" << std::endl;
}


}
