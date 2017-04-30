//
//  Lexer.cpp
//  InferenceEngine
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan on 30/04/2017
//  Copyright (c) 2016 Jacob Milligan. All rights reserved.
//

#include "InferenceEngine/Parsing/Private/Lexer.hpp"

#include <cassert>

namespace ie {


Lexer::Lexer()
    : split_regex_("\\({1}|\\){1}|!{1}|[A-Za-z0-9]+|((=>)|[\\|&]){1}|;{1}"),
      alphanumeric_("[A-Za-z0-9]+")
{
    lexeme_map_ = {
        std::make_pair("&", TokenType::conjunction),
        std::make_pair("|", TokenType::disjunction),
        std::make_pair("!", TokenType::negation),
        std::make_pair("=>", TokenType::implication),
        std::make_pair("TELL", TokenType::tell),
        std::make_pair("tell", TokenType::tell),
        std::make_pair("ASK", TokenType::ask),
        std::make_pair("ask", TokenType::ask),
        std::make_pair(";", TokenType::semicolon),
        std::make_pair("(", TokenType::lparen),
        std::make_pair(")", TokenType::rparen),
        std::make_pair("TRUE", TokenType::truth),
        std::make_pair("true", TokenType::truth),
        std::make_pair("FALSE", TokenType::truth),
        std::make_pair("false", TokenType::falsity)
    };
}

void Lexer::lex(const std::string& str)
{
    tokens_.clear();
    auto begin = std::sregex_token_iterator(str.begin(),
                                            str.end(),
                                            split_regex_);
    auto end = std::sregex_token_iterator();
    TokenType type;

    for ( auto iter = begin; iter != end; ++iter) {

        if ( lexeme_map_.find(iter->str()) != lexeme_map_.end() ) {
            type = lexeme_map_[iter->str()];
        } else if ( std::regex_match(iter->str(), alphanumeric_) ) {
            type = TokenType::symbol;
        } else {
            type = TokenType::unknown;
        }

        tokens_.push_back(Token{ type, iter->str() });
    }

    tokens_.push_back(Token{ TokenType::eof, "" });
}

Lexer::Iterator Lexer::tokbegin()
{
    return tokens_.begin();
}

Lexer::Iterator Lexer::tokend()
{
    return tokens_.end();
}

Token Lexer::token_at(const uint32_t pos)
{
    assert(pos < tokens_.size());
    return tokens_[pos];
}


}