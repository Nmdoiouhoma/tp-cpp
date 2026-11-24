#include <catch2/catch_all.hpp>
import exo9;
using namespace exo9;

TEST_CASE("Exo9") {
    auto tree = BinaryTree<std::string>{};
    auto vec_test = [&](const std::vector<std::string>& result) {
        std::vector<std::string> vec;
        tree.Traversal([&vec](const std::string i) {
        vec.push_back(i);
        });
        REQUIRE(vec == result);
    };
    vec_test({});
    tree.Insert("C++");
    vec_test({"C++"});
    tree.Insert("ASM");
    vec_test({"ASM", "C++"});
    tree.Insert("GO");
    vec_test({"ASM", "C++", "GO"});
    tree.Insert("Rust");
    vec_test({"ASM", "C++", "GO", "Rust"});
    tree.Insert("JavaScript");
    vec_test({"ASM", "C++", "GO", "JavaScript", "Rust"});
}

TEST_CASE("Exo9 Map") {
    auto map = Map<std::string, int>{};

    SECTION("Map vide") {
        REQUIRE(map.GetSize() == 0);
        REQUIRE_FALSE(map.Contains("Jean"));
        REQUIRE_FALSE(map.Find("Jean").has_value());
        REQUIRE_THROWS_AS(map.Get("Jean"), std::out_of_range);
    }

    SECTION("Put crée des entrées") {
        map.Put("Jean", 18);
        map.Put("Georges", 20);
        map.Put("Alice", 30);
        REQUIRE(map.GetSize() == 3);
        REQUIRE(map.Contains("Jean"));
        REQUIRE(map.Contains("Georges"));
        REQUIRE(map.Contains("Alice"));
        REQUIRE_FALSE(map.Contains("Jeanne"));
        REQUIRE(map.Get("Jean") == 18);
        REQUIRE(map.Get("Georges") == 20);
        REQUIRE(map.Get("Alice") == 30);
    }

    SECTION("Put modifie une entrée existante") {
        map.Put("Jean", 18);
        map.Put("Jean", 19);
        REQUIRE(map.GetSize() == 1);
        REQUIRE(map.Get("Jean") == 19);
    }

    SECTION("Get renvoie une référence modifiable") {
        map.Put("Jean", 18);
        map.Get("Jean") = 25;
        REQUIRE(map.Get("Jean") == 25);
    }

    SECTION("Get d'une clé absente") {
        map.Put("Jean", 18);
        REQUIRE_THROWS_AS(map.Get("Jeanne"), std::out_of_range);
    }

    SECTION("Find") {
        map.Put("Jean", 18);
        map.Put("Georges", 20);
        auto jean = map.Find("Jean");
        REQUIRE(jean.has_value());
        REQUIRE(jean->get() == 18);
        REQUIRE_FALSE(map.Find("Jeanne").has_value());
        jean->get() = 40;
        REQUIRE(map.Get("Jean") == 40);
    }

    SECTION("FindExpected") {
        map.Put("Jean", 18);
        map.Put("Georges", 20);
        auto georges = map.FindExpected("Georges");
        REQUIRE(georges.has_value());
        REQUIRE(georges->get() == 20);
        const auto missing = map.FindExpected("Jeanne");
        REQUIRE_FALSE(missing.has_value());
        REQUIRE(missing.error() == "Key not found");
    }

    SECTION("Clear") {
        map.Put("Jean", 18);
        map.Put("Georges", 20);
        map.Clear();
        REQUIRE(map.GetSize() == 0);
        REQUIRE_FALSE(map.Contains("Jean"));
        map.Put("Alice", 30);
        REQUIRE(map.GetSize() == 1);
    }
}
