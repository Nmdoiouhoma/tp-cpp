export module exo3;
import std;

export namespace exo3 {

    struct Vector {
        double x{};
        double y{};
        double z{};

        std::string ToString() const {
            return std::format("({:.2f},{:.2f},{:.2f})", x, y, z);
        }

        constexpr Vector operator+(const Vector& other) const {
            return Vector{x + other.x, y + other.y, z + other.z};
        }

        constexpr Vector operator*(const double factor) const {
            return Vector{x * factor, y * factor, z * factor};
        }

        friend constexpr bool operator==(const Vector& a, const Vector& b) {
            return a.x == b.x && a.y == b.y && a.z == b.z;
        }

        constexpr double LengthSquared() const {
            return x * x + y * y + z * z;
        }
    };

    consteval Vector CreateUnitX() {
        return Vector{1.0, 0.0, 0.0};
    }

    class Application {
    public:
        Application() {
            const auto v1 = Vector{12.34, 56.78, 90.12};
            std::cout << "v1 = " << v1.ToString() << '\n';
            std::cout << "v1 * 2 = " << (v1 * 2.0).ToString() << '\n';
            std::cout << "v1 + (1.1,2.2,3.3) = " << (v1 + Vector{1.1, 2.2, 3.3}).ToString() << '\n';
            std::cout << "LengthSquared(v1) = " << v1.LengthSquared() << '\n';

            constexpr auto unitX = CreateUnitX();
            std::cout << "unitX = " << unitX.ToString() << '\n';

            const auto v2 = v1 + Vector{34.12, 78.56, 12.90};
            std::cout << "v1 == v1 ? " << std::boolalpha << (v1 == v1) << '\n';
            std::cout << "v1 == v2 ? " << (v1 == v2) << '\n';
        }
    };

}
