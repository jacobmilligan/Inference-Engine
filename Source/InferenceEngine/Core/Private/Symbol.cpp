//
// Created by mac on 5/05/17.
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