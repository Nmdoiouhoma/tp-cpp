export module exo2;
import std;

export namespace exo2 {

    class Vector {
    public:
        Vector(const double x, const double y, const double z) : x{x}, y{y}, z{z} {
            std::cout << "Creation d'un Vector\n";
        }

        // recopie d'un vecteur passé par réference
        Vector(const Vector& other) : x{other.x}, y{other.y}, z{other.z} {
            std::cout << "copie d'un vecteur\n";
        }

        //Constructeur par déplacement et remise à 0 des 3 composantes
        Vector (Vector&& other) noexcept :  x{other.x}, y{other.y}, z{other.z}{
            std::cout << "move d'un vecteur\n";
            other.x = 0.0;
            other.y = 0.0;
            other.z = 0.0;

        };
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

        void Sum1(const Vector other) {
            x += other.x;
            y += other.y;
            z += other.z;
        }

        void Sum2(const Vector& other2) {
            x += other2.x;
            y += other2.y;
            z += other2.z;
        }

        std::string ToString() const {
            return std::format("({:.2f},{:.2f},{:.2f})", x, y, z);
        }

        Vector& operator=(const Vector& other) {
            std::cout << "affectation par copie\n";
            x = other.x;
            y = other.y;
            z = other.z;
            return *this;
        }


        Vector& operator=(Vector&& other) noexcept {
            std::cout << "affectation par deplacement\n";
            x = other.x;
            y = other.y;
            z = other.z;
            other.x = 0.0;
            other.y = 0.0;
            other.z = 0.0;
            return *this;
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

            v1.Sum1(v2);
            std::cout << "apres Sum1 = " << v1.ToString() << '\n';

            v1.Sum2(v2);
            std::cout << "apres Sum2 = " << v1.ToString() << '\n';

            auto copy = v1;                       // → "copie d'un vecteur"
            auto moved = std::move(copy);
            std::cout << "moved = " << moved.ToString() << '\n';
            std::cout << "copy = " << copy.ToString() << '\n';
        }
    };

}
