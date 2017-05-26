//
//  Lexer.cpp
//  InferenceEngine
//
//  --------------------------------------------------------------
//
//  Authors:       Jacob Milligan & Cormac Collins
//  Student ID:    100660682 & 100655400
//  Unit:          COS30019 - Introduction To AI
//  Program:       Assignment 2 - Inference Engine
//  Date:          29/04/2017
//

#include "InferenceEngine/Parsing/Private/Lexer.hpp"

#include <cassert>

namespace ie {


Lexer::Lexer()
    : split_regex_("\\({1}|\\){1}|!{1}|[A-Za-z0-9]+|((=>)|[\\|&]){1}|;{1}"),
      alphanumeric_("[A-Za-z0-9]+")
{
    lexeme_map_ = {
        std::make_pair("&", Token{ TokenType::conjunction, "", 3 }),
        std::make_pair("|", Token{ TokenType::disjunction, "", 2 }),
        std::make_pair("!", Token{ TokenType::negation, "", 4 }),
        std::make_pair("=>", Token{ TokenType::implication, "", 1 }),
        std::make_pair("TELL", Token{ TokenType::tell, "", 0 }),
        std::make_pair("tell", Token{ TokenType::tell, "", 0 }),
        std::make_pair("ASK", Token{ TokenType::ask, "", 0 }),
        std::make_pair("ask", Token{ TokenType::ask, "", 0 }),
        std::make_pair(";", Token{ TokenType::semicolon, "", 0 }),
        std::make_pair("(", Token{ TokenType::lparen, "", 0 }),
        std::make_pair(")", Token{ TokenType::rparen, "", 0 }),
        std::make_pair("TRUE", Token{ TokenType::truth, "", 0 }),
        std::make_pair("true", Token{ TokenType::truth, "", 0 }),
        std::make_pair("FALSE", Token{ TokenType::truth, "", 0 }),
        std::make_pair("false", Token{ TokenType::falsity, "", 0 })
    };
}

void Lexer::lex(const std::string& str)
{
    tokens_.clear();
    auto begin = std::sregex_token_iterator(str.begin(),
                                            str.end(),
                                            split_regex_);
    auto end = std::sregex_token_iterator();
    Token tok;

    uint32_t pos = 0;
    for ( auto iter = begin; iter != end; ++iter) {

        if ( lexeme_map_.find(iter->str()) != lexeme_map_.end() ) {
            tok = lexeme_map_[iter->str()];
        } else if ( std::regex_match(iter->str(), alphanumeric_) ) {
            tok.type = TokenType::symbol;
            tok.precedence = 0;
        } else {
            tok.type = TokenType::unknown;
            tok.precedence = 0;
        }

        tok.literal = iter->str();
        tok.pos = pos;

        tokens_.push_back(tok);
        pos++;
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