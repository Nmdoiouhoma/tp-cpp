export module exo5;
import std;

export namespace exo5 {

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

    class Polygon : public Shape {
    public:
        Polygon(std::initializer_list<double> cotés) : cotés{cotés}  {}

        double Perimeter() const override {
            return std::accumulate(cotés.begin(), cotés.end(), 0.0);
        }
        std::string ToString() const override {
            return std::format("Polygone a {} cotes", cotés.size());
        }

    private:
        std::vector<double>cotés {};
    };

    class Rectangle : public Polygon {
    public:
        Rectangle(const double width, const double height) : width(width), height(height), Polygon{width, height, width, height} {}

        std::string ToString() const override {
            return std::format("Rectangle de {:.2f} x {:.2f}", width, height);
        }
    private:
        const double width;
        const double height;
    };

    class Square : public Rectangle {
    public:
        explicit Square(const double side) : Rectangle{side, side}, side{side} {}

        std::string ToString() const override {
            return std::format("Carre de cote {:.2f}", side);
        }

    private:
        double side{};
    };


    class Application {
    public:
        Application() {
            const auto circle = Circle{1.2};
            const auto polygon = Polygon{1.0,2.0,3.0};
            std::cout << circle.ToString() << '\n';
            std::cout << std::format("Perimetre = {:.2f}\n", circle.Perimeter());
            std::cout << polygon.ToString() << '\n';
            std::cout << std::format("Perimeter = {:.2f}\n", polygon.Perimeter());

            const auto rectangle = Rectangle{1.0, 2.0};
            const auto square = Square{1.0};
            std::cout << rectangle.ToString() << '\n';
            std::cout << std::format("Perimeter = {:.2f}\n", rectangle.Perimeter());
            std::cout << square.ToString() << '\n';
            std::cout << std::format("Perimeter = {:.2f}\n", square.Perimeter());
        }
    };

}
