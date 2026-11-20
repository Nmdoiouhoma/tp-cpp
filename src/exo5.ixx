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
        Polygon(const std::initializer_list<double> sides) : sides{sides} {}

        double Perimeter() const override {
            return std::accumulate(sides.begin(), sides.end(), 0.0);
        }

        std::string ToString() const override {
            return std::format("Polygone a {} cotes", sides.size());
        }

    private:
        std::vector<double> sides{};
    };


    class Rectangle : public Polygon {
    public:
        Rectangle(const double width, const double height)
            : Polygon{width, height, width, height}, width{width}, height{height} {}

        std::string ToString() const override {
            return std::format("Rectangle de {:.2f} x {:.2f}", width, height);
        }

    private:
        double width{};
        double height{};
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
            const auto polygon = Polygon{1.0, 2.0, 3.0};
            const auto rectangle = Rectangle{1.0, 2.0};
            const auto square = Square{1.0};

            // Polymorphisme : on manipule toutes les formes comme des Shape
            const auto shapes = std::vector<const Shape*>{&circle, &polygon, &rectangle, &square};
            for (const auto* shape : shapes) {
                std::cout << std::format("{} -> perimetre = {:.2f}\n", shape->ToString(), shape->Perimeter());
            }
        }
    };

}
