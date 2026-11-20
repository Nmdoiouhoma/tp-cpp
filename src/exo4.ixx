export module exo4;
import std;

export namespace exo4 {

    class Shape {
    public:
        virtual ~Shape() = default;

        virtual double Perimeter() const = 0;
        virtual std::string ToString() const = 0;
    };


    class Circle : public Shape {
    public:
        explicit Circle(const double radius) : radius{radius} {}

        double Perimeter() const override {
            return 2.0 * std::numbers::pi * radius;
        }

        std::string ToString() const override {
            return std::format("Cercle de rayon {:.2f}", radius);
        }

    private:
        double radius{};
    };

    class Application {
    public:
        Application() {
            const auto circle = Circle{1.2};
            std::cout << circle.ToString() << '\n';
            std::cout << std::format("Perimetre = {:.2f}\n", circle.Perimeter());
        }
    };

}
