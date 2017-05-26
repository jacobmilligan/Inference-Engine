//
//  Lexer.hpp
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