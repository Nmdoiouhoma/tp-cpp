import exo9;
using namespace exo9;
#include <catch2/catch_all.hpp> 

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
