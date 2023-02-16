#include <array>
#include <iostream>
#include <memory>
#include <vector>
#include <variant>

namespace Explain
{
    template <typename T>
    void foo(T& item)
    {
        std::decay_t<T> value{};
    }
}

void explain()
{
    const int x = 10;
    Explain::foo(x);
}

class Shape // polymorphic wrapper with type-erasure
{
    // shape interface
    class IShape
    {
    public:
        virtual ~IShape() = default;
        virtual void move(int x, int y) = 0;
        virtual void draw() const = 0;
        virtual std::unique_ptr<IShape> clone() = 0;
    };

    template <typename T>
    class ShapeWrapper : public IShape
    {
        T shape_;

    public:
        ShapeWrapper(const T& shp)
            : shape_(shp)
        {
        }

        ShapeWrapper(T&& shp)
            : shape_(std::move(shp))
        {
        }

        void draw() const override
        {
            shape_.draw();
        }

        void move(int x, int y) override
        {
            shape_.move(x, y);
        }

        std::unique_ptr<IShape> clone() override
        {
            return std::make_unique<ShapeWrapper<T>>(shape_);
        }
    };

public:
    template <typename T>
    Shape(T&& shp)
        : shape_(std::make_unique<ShapeWrapper<std::decay_t<T>>>(std::forward<T>(shp)))
    {
    }

    Shape(const Shape& src)
        : shape_{src.shape_->clone()}
    {
    }

    Shape& operator=(const Shape& src)
    {
        Shape temp(src);
        swap(temp);

        return *this;
    }

    template <class T>
    Shape& operator=(T&& src)
    {
        Shape(std::forward<T>(src)).swap(*this);
        return *this;
    }

    Shape(Shape&&) noexcept = default;
    Shape& operator=(Shape&&) noexcept = default;

    void swap(Shape& other)
    {
        shape_.swap(other.shape_);
    }

    void draw() const
    {
        shape_->draw();
    }

    void move(int x, int y)
    {
        shape_->move(x, y);
    }

private:
    std::unique_ptr<IShape> shape_;
};

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