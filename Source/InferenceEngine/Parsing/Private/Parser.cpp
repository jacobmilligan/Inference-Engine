//
//  Parser.cpp
//  InferenceEngine
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan on 29/04/2017
//  Copyright (c) 2016 Jacob Milligan. All rights reserved.
//

#include "InferenceEngine/Parsing/Parser.hpp"
#include "InferenceEngine/AST/Sentence.hpp"
#include "InferenceEngine/AST/Private/ASTPrinter.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>

namespace ie {


void Parser::parse(const sky::Path& filepath)
{
    auto contents = slurp(filepath.str());
    if ( contents.size() <= 0 )
        throw std::length_error("File is empty or does not exist at that path");

    Lexer lexer;
    lexer.lex(contents);

    for (auto iter = lexer.tokbegin(); iter != lexer.tokend(); ++iter) {
        if ( iter->type == TokenType::eof )
            break;

        min_precedence_ = 0;
        ast_.push_back(parse_sentence(iter));
    }
}

std::string Parser::slurp(const std::string& path)
{
    std::ifstream stream(path);
    std::ostringstream contents;
    contents << stream.rdbuf();
    stream.close();

    return contents.str();
}

ASTNode::Child Parser::parse_sentence(Lexer::Iterator& iter)
{
    if ( iter->type == TokenType::tell || iter->type == TokenType::ask )
        ++iter;

    ASTNode::Child lhs;
    ASTNode::Child rhs;
    Token op;
    auto lookahead = *(++iter);
    --iter;

    if ( is_binary(lookahead.type) || iter->type == TokenType::lparen) {
        lhs = parse_complex_sentence(iter);
        op = *iter;
        rhs = parse_complex_sentence(++iter);
        
        if ( is_unary(lookahead) ) {
            return rhs;
        }
        
        lookahead = *(++iter);
        iter--;
        if ( iter->type == TokenType::rparen ) {
            lhs = std::make_unique<ComplexSentence>(
                ComplexSentence(std::move(lhs), op.type, std::move(rhs))
            );

            return std::make_unique<ComplexSentence>(
                ComplexSentence(std::move(lhs),
                                lookahead.type, parse_sentence(++iter))
            );
        }

        return std::make_unique<ComplexSentence>(
            ComplexSentence(std::move(lhs), op.type, std::move(rhs))
        );
    }

    return parse_atomic(iter);
}

ASTNode::Child Parser::parse_complex_sentence(Lexer::Iterator& iter)
{
    ASTNode::Child rhs;
    auto cur = *iter;

    if ( cur.type == TokenType::negation ) {
        return parse_negation(++iter);
    }

    if ( cur.type == TokenType::lparen )
        return parse_sentence(++iter);

    if ( is_atomic(cur) )
        return parse_atomic(iter);

    return nullptr;
}

ASTNode::Child Parser::parse_atomic(Lexer::Iterator& iter)
{
    auto token = *iter;
    ++iter;
    return std::make_unique<AtomicSentence>(AtomicSentence(token));
}

ASTNode::Child Parser::parse_negation(Lexer::Iterator& iter)
{
    return std::make_unique<ComplexSentence>(nullptr, TokenType::negation,
                                             parse_sentence(iter));
}

bool Parser::is_atomic(const Token& cur)
{
    return cur.type == TokenType::symbol;
}

bool Parser::is_binary(const TokenType type)
{
    return type >= TokenType::negation && type < TokenType::symbol;
}

bool Parser::is_unary(const Token& tok)
{
    return tok.type == TokenType::negation;
}

std::vector<ASTNode::Child>& Parser::ast()
{
    return ast_;
}


}