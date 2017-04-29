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

#include <Path/Path.hpp>

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
    ParserTestFixture::root_.append("../Tests");

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
//
//TEST_CASE_METHOD(ParserTestFixture, "Parser opens file correctly", "[parser]")
//{
//    cli_stock_test();
//
//    parser_.parse(cli_.get_positional_result("filename"));
//}