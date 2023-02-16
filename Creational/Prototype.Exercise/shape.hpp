#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "point.hpp"

#include <memory>

namespace Drawing
{
    class Shape
    {
    public:
        virtual ~Shape() = default;
        virtual void move(int x, int y) = 0;
        virtual void draw() const = 0;
        virtual std::unique_ptr<Shape> clone() const = 0;
    };

    template <typename TShape, typename TBaseShape = Shape>
    class CloneableShape : public TBaseShape
    {
    public:
        std::unique_ptr<Shape> clone() const override
        {
            return std::make_unique<TShape>(static_cast<const TShape&>(*this));
        }
    };

    template<typename TShape>
    class ShapeBase : public CloneableShape<TShape>
    {
        Point coord_; // composition
    public:
        Point coord() const
        {
            return coord_;
        }

        void set_coord(const Point& pt)
        {
            coord_ = pt;
        }

        ShapeBase(int x = 0, int y = 0)
            : coord_{x, y}
        {
        }

        void move(int dx, int dy) override
        {
            coord_.translate(dx, dy);
        }
    };
}

#endif // SHAPE_HPP
