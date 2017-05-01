//
//  Lexer.hpp
//  InferenceEngine
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan on 29/04/2017
//  Copyright (c) 2016 Jacob Milligan. All rights reserved.
//

#pragma once

#include <string>
#include <vector>
#include <regex>
#include <unordered_map>


namespace ie {


enum class TokenType {
    negation = 0, // !
    conjunction, // &
    disjunction, // |
    implication, // =>
    symbol, // p, q, p1 etc.
    truth,
    falsity,
    tell,
    ask,
    semicolon,
    lparen,
    rparen,
    eof,
    unknown
};

struct Token {
    TokenType type;
    std::string literal;
    uint16_t precedence;
    uint32_t pos;
};

class Lexer {
public:
    using Iterator = std::vector<Token>::iterator;
    using ReverseIterator = std::vector<Token>::reverse_iterator;

    Lexer();

    void lex(const std::string& str);

    Token token_at(const uint32_t pos);

    Iterator tokbegin();
    Iterator tokend();
private:
    std::unordered_map<std::string, Token> lexeme_map_;
    std::vector<Token> tokens_;
    std::regex split_regex_;
    std::regex alphanumeric_;
};


}