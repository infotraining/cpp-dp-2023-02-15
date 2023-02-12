#define CATCH_CONFIG_MAIN

#include "ast.hpp"
#include "visitors.hpp"
#include "catch.hpp"

using namespace AST;
using namespace AST::helpers;

TEST_CASE("expression evaluator visitor", "[ast]")
{
    ExprEvalVisitor visitor;

    SECTION("integer")
    {
        auto expr = integer(4);
        expr->accept(visitor);

        REQUIRE(visitor.result() == 4);
    }

    SECTION("addition")
    {
        auto expr = add(integer(1), integer(2));
        expr->accept(visitor);

        REQUIRE(visitor.result() == 3);
    }

    SECTION("multiplication")
    {
        auto expr = multiply(integer(2), integer(3));
        expr->accept(visitor);

        REQUIRE(visitor.result() == 6);
    }

    SECTION("composite expression")
    {
        auto expr = add(integer(3), multiply(integer(2), integer(5)));

        expr->accept(visitor);

        REQUIRE(visitor.result() == 13);
    }
}

TEST_CASE("printing visitor")
{
    // TODO - uncomment tests

    // PrintingVisitor visitor;

    // SECTION("integer")
    // {
    //     auto expr = integer(4);
    //     expr->accept(visitor);

    //     REQUIRE(visitor.str() == "4");
    // }

    // SECTION("addition")
    // {
    //     auto expr = add(integer(1), integer(2));
    //     expr->accept(visitor);

    //     REQUIRE(visitor.str() == "(1 + 2)");
    // }

    // SECTION("multiplication")
    // {
    //     auto expr = multiply(integer(2), integer(3));
    //     expr->accept(visitor);

    //     REQUIRE(visitor.str() == "(2 * 3)");
    // }

    // SECTION("composite expression")
    // {
    //     auto expr = add(integer(3), multiply(integer(2), integer(5)));

    //     expr->accept(visitor);

    //     REQUIRE(visitor.str() == "(3 + (2 * 5))");
    // }
}
