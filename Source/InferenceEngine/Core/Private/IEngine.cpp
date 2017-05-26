//
//  IEngine.cpp
//  iengine
//
//  --------------------------------------------------------------
//
//  Authors:       Jacob Milligan & Cormac Collins
//  Student ID:    100660682 & 100655400
//  Unit:          COS30019 - Introduction To AI
//  Program:       Assignment 2 - Inference Engine
//  Date:          25/05/2017
//

#include "InferenceEngine/Core/IEngine.hpp"

namespace ie {


void IEngine::infer(const std::string& method_str, const sky::Path& filepath)
{
    auto method = get_method(method_str);
    if ( method == InferenceMethod::unknown ) {
        std::cout << "iengine: invalid inference method '"
                  << method_str << "'\n";
        std::cout << "Expected one of: TT, FC, BC" << std::endl;
        return;
    }

    auto pre = parser_.preprocess(filepath);
    if ( pre.tell == "ERROR" ) {
        std::cout << "iengine: " << pre.ask << std::endl;
        return;
    }

    Parser tell;
    tell.parse(pre.tell);
    kb_.tell(tell.ast());

    Parser ask;
    ask.parse(pre.ask);
    parser_.parse(pre.ask);

    parser_.ast()[0]->accept(finder_);

    auto q = Symbol(finder_.symbols()[0], false);

    kb_.ask(method, q);
}

InferenceMethod IEngine::get_method(const std::string& method_str)
{
    std::string lower = method_str;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    auto method = InferenceMethod::unknown;

    if ( lower == "tt"  )
        method = InferenceMethod::TT;
    if ( lower == "bc"  )
        method = InferenceMethod::BC;
    if ( lower == "fc"  )
        method = InferenceMethod::FC;

    return method;
}


}