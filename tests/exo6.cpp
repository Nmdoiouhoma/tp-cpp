#include <catch2/catch_all.hpp>

import exo6;
using namespace exo6;

TEST_CASE("Exo6") {
    auto vec = std::vector{1, 4, 5, 2, 1, 7, 8, 5, 8, 2, 9};

    VectorUtils::SortAndRemoveDuplicates(vec);
    REQUIRE(vec == std::vector{1, 2, 4, 5, 7, 8, 9});

    REQUIRE(VectorUtils::CountGreaterThan(vec, 5) == 3);

    auto greater = std::vector<int>{};
    for (const int value : VectorUtils::GreaterThan(vec, 5)) {
        greater.push_back(value);
    }
    REQUIRE(greater == std::vector{7, 8, 9});

    const auto array = std::array{1, 6, 2, 7};
    REQUIRE(VectorUtils::CountGreaterThan(array, 5) == 2);
}
