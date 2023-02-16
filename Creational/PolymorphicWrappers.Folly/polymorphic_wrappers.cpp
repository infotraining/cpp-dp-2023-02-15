#include <array>
#include <folly/Poly.h>
#include <iostream>
#include <memory>
#include <vector>

struct IShape
{
    template <class Base>
    struct Interface : Base
    {
        void move(int dx, int dy) { folly::poly_call<0>(*this, dx, dy); }
        void draw() const { folly::poly_call<1>(*this); }
    };

    template <class T>
    using Members = folly::PolyMembers<&T::move, &T::draw>;
};

using Shape = folly::Poly<IShape>;

struct Circle
{
    int x, y;
    int r;

    Circle(int x, int y, int r)
        : x{x}
        , y{y}
        , r{r}
    {
    }

    void draw() const
    {
        std::cout << "Circle([" << x << ", " << y << "], " << r << ")\n";
    }

    void move(int dx, int dy)
    {
        x += dx;
        y += dy;
    }
};

struct Square
{
    int x, y;
    int size;

    Square(int x, int y, int r)
        : x{x}
        , y{y}
        , size{r}
    {
    }

    void draw() const
    {
        std::cout << "Square([" << x << ", " << y << "], " << size << ")\n";
    }

    void move(int dx, int dy)
    {
        x += dx;
        y += dy;
    }
};

struct Point
{
    int x, y;
};

struct Triangle
{
    std::array<Point, 3> vertices;

    void draw() const
    {
        std::cout << "Triangle({ ";
        for (const Point& v : vertices)
            std::cout << "[" << v.x << ", " << v.y << "]"
                      << " ";
        std::cout << "})\n";
    }

    void move(int dx, int dy)
    {
        for (auto& v : vertices)
        {
            v.x += dx;
            v.y += dy;
        }
    }
};

class GraphicsDoc
{
    std::vector<Shape> shapes_;

public:
    GraphicsDoc() = default;

    GraphicsDoc(const std::vector<Shape>& shapes)
        : shapes_(shapes)
    {
    }

    void add(Shape shp)
    {
        shapes_.push_back(shp);
    }

    void draw() const
    {
        std::cout << "GraphicsDoc{\n";
        for (const auto& shp : shapes_)
        {
            std::cout << " + ";
            shp.draw();
        }
        std::cout << "}\n";
    }

    void move(int dx, int dy)
    {
        for (auto& shp : shapes_)
            shp.move(dx, dy);
    }
};

int main(int argc, char* argv[])
{
    auto c = Circle(1, 2, 10);

    Shape shp1 = Circle(1, 2, 10);
    shp1.draw();
    shp1 = Square(50, 10, 120);

    std::cout << "\n\n";

    Shape shp2 = shp1;
    shp1 = Square(30, 40, 100);

    shp1.draw();
    shp2.draw();

    std::cout << "\n\n";

    Shape shp3 = Circle(10, 20, 100);
    Shape shp4 = Square(100, 200, 10);    
    Shape temp = shp3;
    shp3 = shp4;
    shp4 = temp;

    shp3.draw();
    shp4.draw();

    std::cout << "\n\n";

    std::vector<Shape> shapes = {shp1, shp2, Circle(100, 200, 2), Square{10, 20, 300}, Triangle{{Point{0, 10}, Point{10, 20}, Point{40, 70}}}};

    shp1.move(10, 1000);
    shp1.draw();

    for (const auto& shp : shapes)
        shp.draw();

    std::cout << "\n\n";
    std::cout << "Graphics document:\n";

    GraphicsDoc doc(shapes);
    doc.add(Circle(1, 1, 20));
    doc.add(Square(2, 3, 10));
    doc.draw();

    std::cout << "\n\nMoving coordinates:\n";
    doc.move(1, 2);
    doc.draw();
}