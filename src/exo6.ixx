export module exo6;
import std;

export namespace exo6 {

    class VectorUtils {
    public:
        static void Print(std::span<const int> values, std::string_view label = {}) {
            if (!label.empty()) {
                std::cout << label << ": ";
            }
            std::ranges::for_each(values, [](int value) {
                std::cout << value << " ";
            });
            std::cout << '\n';
        }

        static void SortAndRemoveDuplicates(std::vector<int>& vec) {
            std::ranges::sort(vec);
            const auto duplicates = std::ranges::unique(vec);
            vec.erase(duplicates.begin(), duplicates.end());
        }

        static int CountGreaterThan(std::span<const int> values, int threshold) {
            return static_cast<int>(std::ranges::count_if(values, [threshold](int value) {
                return value > threshold;
            }));
        }

        static auto GreaterThan(std::span<const int> values, int threshold) {
            return values | std::views::filter([threshold](int value) {
                return value > threshold;
            });
        }
    };

    class Application {
    public:
        Application() {
            auto vec = std::vector{1, 4, 5, 2, 1, 7, 8, 5, 8, 2, 9};
            VectorUtils::Print(vec, "avant");

            VectorUtils::SortAndRemoveDuplicates(vec);
            VectorUtils::Print(vec, "apres tri");

            std::cout << "plus grands que 5 : " << VectorUtils::CountGreaterThan(vec, 5) << '\n';
            for (const int value : VectorUtils::GreaterThan(vec, 5)) {
                std::cout << value << ' ';
            }
            std::cout << '\n';

            const auto array = std::array{1, 6, 2, 7};
            VectorUtils::Print(array, "array");
            std::cout << "array plus grands que 5 : " << VectorUtils::CountGreaterThan(array, 5) << '\n';
        }
    };

}
