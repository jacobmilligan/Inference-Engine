//
//  Symbol.hpp
//  iengine
//
//  --------------------------------------------------------------
//
//  Authors:       Jacob Milligan & Cormac Collins
//  Student ID:    100660682 & 100655400
//  Unit:          COS30019 - Introduction To AI
//  Program:       Assignment 2 - Inference Engine
//  Date:          05/05/2017
//

#pragma once

#include <string>

namespace ie {

    class Symbol {
    private:
        std::string symbolName_;
        bool value_ = false;

    public:


        bool hasConjunctionConnective;
        Symbol();

        Symbol(std::string s, bool val) : symbolName_ (s), value_(val) {};

        bool GetValue() const;

        std::string GetSymbolName() const;

        void SetValue(bool val);
    };
}
