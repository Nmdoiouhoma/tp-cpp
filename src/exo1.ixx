export module exo1;
import std;

export namespace exo1 {

    class Vector {
    public:
        Vector(const double x, const double y, const double z) : x{x}, y{y}, z{z} {}

        double GetX() const { return x; }
        double GetY() const { return y; }
        double GetZ() const { return z; }

        void SetX(const double value) { x = value; }
        void SetY(const double value) { y = value; }
        void SetZ(const double value) { z = value; }

        void Homothety(const double factor) {
            x *= factor;
            y *= factor;
            z *= factor;
        }

        void Sum(const Vector other) {
            x += other.x;
            y += other.y;
            z += other.z;
        }

        std::string ToString() const {
            return std::format("({:.2f},{:.2f},{:.2f})", x, y, z);
        }

    private:
        double x{0.0};
        double y{0.0};
        double z{0.0};
    };

    class Application {
    public:
        Application() {
            auto v1 = Vector{12.34, 34.56, 56.78};
            std::cout << "v1 = " << v1.ToString() << '\n';

            v1.Homothety(2.1);
            std::cout << "v1 * 2.1 = " << v1.ToString() << '\n';

            v1.SetX(34.12);
            v1.SetY(56.34);
            v1.SetZ(78.56);
            std::cout << "v1 modifie = " << v1.ToString() << '\n';

            const auto v2 = Vector{1.1, 2.2, 3.3};
            std::cout << "v2 = " << v2.ToString() << '\n';

            v1.Sum(v2);
            std::cout << "v1 + v2 = " << v1.ToString() << '\n';
        }
    };

}
