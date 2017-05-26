//
//  Model.cpp
//  iengine
//
//  --------------------------------------------------------------
//
//  Authors:       Jacob Milligan & Cormac Collins
//  Student ID:    100660682 & 100655400
//  Unit:          COS30019 - Introduction To AI
//  Program:       Assignment 2 - Inference Engine
//  Date:          22/05/2017
//

#include "InferenceEngine/TT/Model.hpp"

namespace ie {


bool Model::is_true(const std::string& symbol) const
{
    if ( values_.find(symbol) == values_.end() )
        return false;

    return values_.at(symbol);
}

bool
Model::is_true(const std::unordered_map<std::string, const Sentence*>& sentences) const
{
    ResolutionVisitor visitor;
    bool result = true;
    // Conjunction of clauses
    for ( auto& s : sentences ) {
        result = result && visitor.get_solution(values_, *(s.second));
    }
    return result;
}

Model Model::extend(const std::string& symbol, const bool value) const
{
    auto result = *this;
    result.values_[symbol] = value;
    return result;
}


}