//
//  BackwardChaining.hpp
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

#pragma once

#include "InferenceEngine/Core/Symbol.hpp"
#include "InferenceEngine/BC/BCatomic.hpp"

/// @brief Wrapper for entire premise both lhs and rhs
namespace ie {
    class PremiseWrapper{
    public:
        PremiseWrapper(std::string rhs, BCatomic lhs) : rhs_(rhs), lhs_(lhs){}
        std::string rhs_;
        BCatomic lhs_;
    };

}
