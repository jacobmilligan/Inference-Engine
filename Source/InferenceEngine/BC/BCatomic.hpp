//
//  BCAtomic.hpp
//  iengine
//
//  --------------------------------------------------------------
//
//  Authors:       Jacob Milligan & Cormac Collins
//  Student ID:    100660682 & 100655400
//  Unit:          COS30019 - Introduction To AI
//  Program:       Assignment 2 - Inference Engine
//  Date:          24/05/2017
//

#include "InferenceEngine/Core/Symbol.hpp"

#pragma once

///@brief container for lhs atomic values and tokens during BC search
namespace ie {
    class BCatomic{
    public:
        BCatomic(std::vector<std::string>& symListlhs, std::stack<TokenType> tokens)
            : symbol_lhs_(symListlhs), token(tokens)
        {}
        std::vector<std::string> symbol_lhs_;
        std::stack<TokenType> token;
    };
}
