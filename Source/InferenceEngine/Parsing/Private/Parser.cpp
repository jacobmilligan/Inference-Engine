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

        ast_.push_back(parse_sentence(iter, 0));
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

ASTNode::Child Parser::parse_sentence(Lexer::Iterator& iter, const uint32_t prec)
{
    if ( iter->type == TokenType::tell || iter->type == TokenType::ask )
        ++iter;

    ASTNode::Child lhs;
    lhs = parse_atomic(iter);

    Token op;
    while ( true ) {
        op = *iter;

        if ( !is_binary(op.type) || op.precedence < prec )
            break;

        auto next_prec = prec + 2;
        ++iter;
        auto rhs = parse_sentence(iter, next_prec);
        lhs = parse_connective(lhs, op, rhs);
    }

    return lhs;
}

ASTNode::Child Parser::parse_atomic(Lexer::Iterator& iter)
{
    auto token = *iter;
    if ( token.type == TokenType::lparen ) {
        auto val = parse_sentence(++iter, 1);
        if ( iter->type != TokenType::rparen ) {
            std::string msg = "Unmatched '(' at pos:";
            msg += std::to_string(iter->pos);
            throw msg;
        }

        ++iter;
        return val;
    }

    if ( token.type == TokenType::negation ) {
        return parse_negation(++iter, token.precedence);
    }

    ++iter;
    return std::make_unique<AtomicSentence>(AtomicSentence(token));
}

ASTNode::Child Parser::parse_negation(Lexer::Iterator& iter, const uint32_t prec)
{
    return std::make_unique<ComplexSentence>(ComplexSentence(
        nullptr, TokenType::negation, parse_sentence(iter, prec + 1))
    );
}

ASTNode::Child Parser::parse_connective(ASTNode::Child& lhs, const Token& connective,
                                        ASTNode::Child& rhs)
{
    if ( lhs == nullptr ) {
        std::string msg = "Unexpected NULL at position ";
        msg += std::to_string(connective.pos - 1);

        std::cout << msg;

        throw msg;
    }
    return std::make_unique<ComplexSentence>(ComplexSentence(
        std::move(lhs), connective.type, std::move(rhs))
    );
}

bool Parser::is_binary(const TokenType type)
{
    return type >= TokenType::negation && type < TokenType::symbol;
}

std::vector<ASTNode::Child>& Parser::ast()
{
    return ast_;
}


}