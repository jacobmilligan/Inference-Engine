//
// Created by mac on 24/05/17.
//

#include <InferenceEngine/Core/Symbol.hpp>
#include <InferenceEngine/Parsing/Private/Lexer.hpp>

#ifndef IENGINE_BCATOMIC_HPP
#define IENGINE_BCATOMIC_HPP
/// -----------------------------------------------------------
///container for lhs atomic values and tokens during BC search
// ------------------------------------------------------------
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


#endif //IENGINE_BCATOMIC_HPP