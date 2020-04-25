#include <catch2/catch.hpp>

#include "TestUtils.h"

TEST_CASE("example") {
    SECTION("addition") {
        REQUIRE(2 + 2 == 4);
    }
    SECTION("substraction") {
        REQUIRE(2 - 2 == 0);
    }
}
