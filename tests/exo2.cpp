#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

// Importation de l'exercice
import exo2;
using namespace exo2;

TEST_CASE("Exo2", "[Vector]") {
    Vector v1{12.34, 34.56, 56.78};
    REQUIRE(v1.ToString() == "(12.34,34.56,56.78)");
    Vector v2{1.1, 2.2, 3.3};
    v1.Sum1(v2);
    REQUIRE(v1.ToString() == "(13.44,36.76,60.08)");
    v1.Sum2(v2);
    REQUIRE(v1.ToString() == "(14.54,38.96,63.38)");
    auto copy = v1;
    auto moved = std::move(copy);
    REQUIRE(moved.ToString() == "(14.54,38.96,63.38)");
    REQUIRE(copy.ToString() == "(0.00,0.00,0.00)");
    auto assigned = Vector{0.0, 0.0, 0.0};
    assigned = moved;
    REQUIRE(assigned.ToString() == "(14.54,38.96,63.38)");
    assigned = std::move(moved);
    REQUIRE(assigned.ToString() == "(14.54,38.96,63.38)");
    REQUIRE(moved.ToString() == "(0.00,0.00,0.00)");
}
