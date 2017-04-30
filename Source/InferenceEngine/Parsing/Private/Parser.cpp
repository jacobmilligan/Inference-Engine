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

namespace ie {


void Parser::parse(const sky::Path& filepath)
{
    auto contents = slurp(filepath.str());
    Lexer lexer;
    lexer.lex(contents);

    for (auto iter = lexer.tokbegin(); iter != lexer.tokend(); ++iter) {
        if ( iter->type == TokenType::eof )
            break;

        ast_.push_back(parse_sentence(iter));
    }

    ie::ASTPrinter printer;
    for ( auto& n : ast_ ) {
        n->accept(printer);
        std::cout << ";";
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
    if ( iter->type == TokenType::ask || iter->type == TokenType::tell )
        ++iter;

    auto lookahead = ++iter;
    iter--;

    switch (lookahead->type) {
        case TokenType::conjunction:
        case TokenType::disjunction:
        case TokenType::implication:
        case TokenType::negation:
            return parse_complex_sentence(iter);
        default:
            break;
    }

    switch (iter->type) {
        case TokenType::symbol: return parse_atomic(iter);

        case TokenType::truth:break;
        case TokenType::falsity:break;

        case TokenType::ask:
        case TokenType::tell:
            ++iter;
            break;

        case TokenType::semicolon:break;
        case TokenType::lparen: return parse_sentence(++iter);
        case TokenType::rparen: //throw error on not symbol
            break;

        case TokenType::eof:break;
        case TokenType::unknown:break;
    }

    auto complex = parse_complex_sentence(iter);
    ++iter;
    return complex;
}

ASTNode::Child Parser::parse_complex_sentence(Lexer::Iterator& iter)
{
    ASTNode::Child lhs;

    if ( iter->type == TokenType::lparen )
        lhs = parse_sentence(++iter);

    if ( iter->type == TokenType::symbol )
        lhs = parse_atomic(iter);

    if ( iter->type == TokenType::negation )
        lhs = nullptr;

    return std::make_unique<ComplexSentence>(
        ComplexSentence(std::move(lhs), iter->type, parse_sentence(++iter))
    );
}

ASTNode::Child Parser::parse_atomic(Lexer::Iterator& iter)
{
    auto token = *iter;
    ++iter;
    return std::make_unique<AtomicSentence>(AtomicSentence(token));
}

ASTNode::Child Parser::parse_negation(Lexer::Iterator& iter)
{
    return std::make_unique<ComplexSentence>(nullptr, iter->type,
                                             parse_sentence(++iter));
}

}