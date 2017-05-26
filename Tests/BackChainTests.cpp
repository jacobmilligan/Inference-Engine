//
// Created by mac on 19/05/17.
//

#include <InferenceEngine/FC/ForwardChaining.hpp>

#define CATCH_CONFIG_RUNNER
#include <catch/catch.hpp>
#include <InferenceEngine/BC/BackwardChaining.hpp>
#include <InferenceEngine/Core/IEngine.hpp>
#include "CoutUtils.hpp"

sky::Path root("");

int main(int argc, char** argv)
{
    root.assign(sky::Path::bin_path(argv));
    root.append("../../Tests");

    int result = Catch::Session().run(argc, argv);

    return ( result < 0xff ? result : 0xff );
}


TEST_CASE("Forward chaining assignment answer", "[bc]")
{
    CoutUtils cout_utils;

    auto file = root.get_relative("test1.txt");
    auto method = "BC";

    ie::IEngine engine;

    cout_utils.redirect_cout();
    engine.infer(method, sky::Path(file));
    REQUIRE(cout_utils.get_cout() == "YES: p2, p3, p1, d");
    cout_utils.reset_cout();
}

TEST_CASE("large conjunctino lhs", "[bc]")
{
    CoutUtils cout_utils;

    auto file = root.get_relative("test6.txt");
    auto method = "BC";

    ie::IEngine engine;

    cout_utils.redirect_cout();
    engine.infer(method, sky::Path(file));
    REQUIRE(cout_utils.get_cout() == "YES: a, b, c, d, e, k1");
    cout_utils.reset_cout();
}

TEST_CASE("large dysjunction lhs", "[bc]")
{
    CoutUtils cout_utils;

    auto file = root.get_relative("test11.txt");
    auto method = "BC";

    ie::IEngine engine;

    cout_utils.redirect_cout();
    engine.infer(method, sky::Path(file));
    REQUIRE(cout_utils.get_cout() == "YES: a, k1");
    cout_utils.reset_cout();
}

TEST_CASE("finds faster route", "[bc]")
{
    CoutUtils cout_utils;

    auto file = root.get_relative("test12.txt");
    auto method = "BC";

    ie::IEngine engine;

    cout_utils.redirect_cout();
    engine.infer(method, sky::Path(file));
    REQUIRE(cout_utils.get_cout() == "YES: k2, z");
    cout_utils.reset_cout();
}

TEST_CASE("complex route", "[bc]")
{
    CoutUtils cout_utils;

    auto file = root.get_relative("test13.txt");
    auto method = "BC";

    ie::IEngine engine;

    cout_utils.redirect_cout();
    engine.infer(method, sky::Path(file));
    REQUIRE(cout_utils.get_cout() == "YES: d, r1, r2, a, b, x");
    cout_utils.reset_cout();
}

TEST_CASE("simple route 1", "[bc]")
{
    CoutUtils cout_utils;

    auto file = root.get_relative("test14.txt");
    auto method = "BC";

    ie::IEngine engine;

    cout_utils.redirect_cout();
    engine.infer(method, sky::Path(file));
    REQUIRE(cout_utils.get_cout() == "YES: a, b, k1, z");
    cout_utils.reset_cout();
}

TEST_CASE("goal truth already given in atomic value", "[bc]")
{
    CoutUtils cout_utils;

    auto file = root.get_relative("test15.txt");
    auto method = "BC";

    ie::IEngine engine;

    cout_utils.redirect_cout();
    engine.infer(method, sky::Path(file));
    REQUIRE(cout_utils.get_cout() == "YES: b");
    cout_utils.reset_cout();
}


TEST_CASE("no solution in close solve conjunctions", "[bc]")
{
    CoutUtils cout_utils;

    auto file = root.get_relative("test16.txt");
    auto method = "BC";

    ie::IEngine engine;

    cout_utils.redirect_cout();
    engine.infer(method, sky::Path(file));
    REQUIRE(cout_utils.get_cout() == "NO");
    cout_utils.reset_cout();
}