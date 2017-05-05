//
//  Skeleton.cpp
//  InferenceEngine
//  A blank file to demonstrate how to add unit tests
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan on 29/04/2017
//  Copyright (c) 2016 Jacob Milligan. All rights reserved.
//

#define CATCH_CONFIG_RUNNER
#include <catch/catch.hpp>

#include <InferenceEngine/Parsing/CLIParser.hpp>
#include <InferenceEngine/Parsing/Parser.hpp>
#include <InferenceEngine/Parsing/Private/Lexer.hpp>
#include <InferenceEngine/AST/Private/ASTPrinter.hpp>

#include <Path/Path.hpp>
#include <InferenceEngine/AST/SymbolFinder.hpp>

class ParserTestFixture {
public:
    static sky::Path root_;

    ParserTestFixture()
        : cli_("test app", "Runs unit tests")
    {}

    int get_argc(const size_t argvsize, char** argv)
    {
        return (int)(( argvsize / sizeof(argv[0] )) - 1 );
    }

    void redirect_cout()
    {
        ss_.clear();
        ss_.str("");
        coutbuf_ = std::cout.rdbuf(ss_.rdbuf());
    }

    std::string get_cout()
    {
        return ss_.str();
    }

    void reset_cout()
    {
        std::cout.rdbuf(coutbuf_);
    }

    void print_help()
    {
        char file[] = "/usr/bin/test_file";
        char help[] = "-h";
        char* argv[] = { &file[0], &help[0], nullptr };
        auto argc = get_argc(sizeof(argv), argv);

        cli_.parse(argc, argv);
    }

    void cli_stock_test()
    {
        cli_ = ie::CLIParser("iengine", "Knowledge-Base engine");
        cli_.add_positional(ie::CLIArgument("method",
                                            "The inference method to use to "
                                                "check for entailment"));
        cli_.add_positional(ie::CLIArgument("filename",
                                            "The file to read the Knowledge-Base from. Specified as relative "
                                                "path from the binary directory"
        ));

        char pos1[] = "TT";
        char pos2[] = "test1.txt";
        char* argv[] = { &root_.str()[0], &pos1[0], &pos2[0], nullptr };
        auto argc = get_argc(sizeof(argv), argv);

        cli_.parse(argc, argv);
    }

protected:
    ie::CLIParser cli_;
    ie::Parser parser_;
private:
    std::stringstream ss_;
    std::streambuf* coutbuf_;
};

sky::Path ParserTestFixture::root_ = "";

int main(int argc, char** argv)
{
    ParserTestFixture::root_.assign(sky::Path::bin_path(argv));
    ParserTestFixture::root_.append("../../Tests");

    int result = Catch::Session().run(argc, argv);

    return ( result < 0xff ? result : 0xff );
}

TEST_CASE_METHOD(ParserTestFixture, "CLI parser prints help", "[help]")
{
    redirect_cout();
    print_help();
    reset_cout();

    REQUIRE(get_cout() == cli_.help_string() + "\n");
}

TEST_CASE_METHOD(ParserTestFixture, "CLI prints positional args in help", "[help]")
{
    cli_.reset();
    cli_.add_positional(ie::CLIArgument("test", "tests positionals"));

    auto found = cli_.help_string().find("<test>");

    REQUIRE(found != std::string::npos);
}

TEST_CASE_METHOD(ParserTestFixture, "CLI parses", "[cli]")
{
    cli_.reset();
    cli_.add_positional(ie::CLIArgument("test", "test positional"));
    cli_.add_positional(ie::CLIArgument("test2", "test positional again"));

    char file[] = "/usr/bin/test_file";
    char pos1[] = "jacob";
    char pos2[] = "cormac";
    char* argv[] = { &file[0], &pos1[0], &pos2[0], nullptr };
    auto argc = get_argc(sizeof(argv), argv);

    cli_.parse(argc, argv);

    REQUIRE(cli_.get_positional_result("test") == "jacob");
    REQUIRE(cli_.get_positional_result("test2") == "cormac");
}

TEST_CASE_METHOD(ParserTestFixture, "CLI parses app correctly", "[cli]")
{
    cli_stock_test();

    REQUIRE(cli_.get_positional_result("method") == "TT");
    REQUIRE(cli_.get_positional_result("filename") == "test1.txt");
}

TEST_CASE_METHOD(ParserTestFixture, "Lexer tokenizes correctly", "[lexer]")
{
    auto lexer = ie::Lexer();
    std::string kb_string = "TELL\n"
        "p2=> p3; p3 => p1; c => e; b&e => f; f&g => h; p1=>d; p1&p3 => c; a; b; p2; f| g;(p&g) => (p |g) & !a;\n"
        "ASK\n"
        "d";

    std::vector<ie::TokenType> correct_tokens = {
        ie::TokenType::tell, // 0
        ie::TokenType::symbol, ie::TokenType::implication, ie::TokenType::symbol, // 3
        ie::TokenType::semicolon, // 4
        ie::TokenType::symbol, ie::TokenType::implication, ie::TokenType::symbol, // 7
        ie::TokenType::semicolon, // 8
        ie::TokenType::symbol, ie::TokenType::implication, ie::TokenType::symbol, // 11
        ie::TokenType::semicolon, // 12
        ie::TokenType::symbol, ie::TokenType::conjunction, ie::TokenType::symbol, ie::TokenType::implication, ie::TokenType::symbol, // 17
        ie::TokenType::semicolon, // 18
        ie::TokenType::symbol, ie::TokenType::conjunction, ie::TokenType::symbol, ie::TokenType::implication, ie::TokenType::symbol, // 23
        ie::TokenType::semicolon, // 24
        ie::TokenType::symbol, ie::TokenType::implication, ie::TokenType::symbol, // 27
        ie::TokenType::semicolon, // 28
        ie::TokenType::symbol, ie::TokenType::conjunction, ie::TokenType::symbol, ie::TokenType::implication, ie::TokenType::symbol, // 33
        ie::TokenType::semicolon, // 34
        ie::TokenType::symbol, // 35
        ie::TokenType::semicolon, // 36
        ie::TokenType::symbol, // 37
        ie::TokenType::semicolon, // 38
        ie::TokenType::symbol, // 39
        ie::TokenType::semicolon, // 40
        ie::TokenType::symbol, ie::TokenType::disjunction, ie::TokenType::symbol, // 43
        ie::TokenType::semicolon, // 44
        ie::TokenType::lparen, ie::TokenType::symbol, ie::TokenType::conjunction, ie::TokenType::symbol, ie::TokenType::rparen, ie::TokenType::implication, ie::TokenType::lparen, ie::TokenType::symbol, ie::TokenType::disjunction, ie::TokenType::symbol, ie::TokenType::rparen, ie::TokenType::conjunction, ie::TokenType::negation, ie::TokenType::symbol, // 58
        ie::TokenType::semicolon, // 59
        ie::TokenType::ask, // 60
        ie::TokenType::symbol, // 61
    };

    lexer.lex(kb_string);

    unsigned long index = 0;
    for (auto iter = lexer.tokbegin(); iter != lexer.tokend(); ++iter) {
        INFO("Token: " << index << " Lexeme: " << iter->literal);
        REQUIRE(iter->type == correct_tokens[index]);
        index++;
    }
}

TEST_CASE_METHOD(ParserTestFixture, "Parser reads file", "[parser]")
{
    auto file = root_.get_relative("test1.txt");
    ie::Parser parser;
    REQUIRE_NOTHROW(parser.parse(sky::Path(file)));
}

TEST_CASE_METHOD(ParserTestFixture, "Parser gets grammer right", "[parser]")
{
    auto path = root_.get_relative("test1.txt");

    ie::Parser parser;
    parser.parse(path);

    ie::ASTPrinter printer;

    for ( auto& n : parser.ast() ) {
        redirect_cout();
        n->accept(printer);
        reset_cout();

        REQUIRE(get_cout() == "hey");
    }
}

TEST_CASE_METHOD(ParserTestFixture, "SymbolFinder gets all symbols test1.txt", "[ASTvisitor]")
{
    auto file = root_.get_relative("test1.txt");
    ie::Parser parser;


    parser.parse(sky::Path(file));

    ie::SymbolFinder s;

    for(auto& a: parser.ast()){
        a->accept(s);
    }

    std::string outputString;

    for(auto a : s.GetSymbols()) {
        outputString += a + " ";
    }

    REQUIRE(outputString == "p3 p2 p1 p3 e c e b f g f h d p1 p3 p1 c a b p2 d ");
}

TEST_CASE_METHOD(ParserTestFixture, "SymbolFinder gets all symbols test2.txt", "[ASTvisitor]")
{
    auto file = root_.get_relative("test2.txt");
    ie::Parser parser;


    parser.parse(sky::Path(file));

    ie::SymbolFinder s;

    for(auto& a: parser.ast()){
        a->accept(s);
    }

    std::string outputString;

    for(auto a : s.GetSymbols()) {
        outputString += a + " ";
    }

    REQUIRE(outputString == "d p2 e e p4 p d ");
}

TEST_CASE_METHOD(ParserTestFixture, "SymbolFinder gets all symbols test3.txt", "[ASTvisitor]")
{
    auto file = root_.get_relative("test3.txt");
    ie::Parser parser;


    parser.parse(sky::Path(file));

    ie::SymbolFinder s;

    for(auto& a: parser.ast()){
        a->accept(s);
    }

    std::string outputString;

    for(auto a : s.GetSymbols()) {
        outputString += a + " ";
    }

    REQUIRE(outputString == "d p2 e e p4 p d ");
}