//
// Created by mac on 5/05/17.
//

#ifndef PROJECT_SYMBOL_HPP
#define PROJECT_SYMBOL_HPP

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


#endif //PROJECT_SYMBOL_HPP
