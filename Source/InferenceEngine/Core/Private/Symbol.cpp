//
//  Symbol.cpp
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

#include "InferenceEngine/Core/Symbol.hpp"

namespace ie {

    bool Symbol::GetValue() const
    {
        return value_;
    }

    std::string Symbol::GetSymbolName() const
    {
        return symbolName_;
    }

    void Symbol::SetValue(bool val) {
        value_ = val;
    }

    Symbol::Symbol() {
        value_ = false;
        symbolName_ = "";
    }
}