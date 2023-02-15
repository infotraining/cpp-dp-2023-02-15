#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.hpp"

namespace Drawing
{
    // TODO - add a circle to Shape hierarchy

    class Circle : public ShapeBase
    {
        int r_;
    public:
        static constexpr auto id = "Circle";

        Circle(int x = 0, int y = 0, int r = 0) : ShapeBase{x, y}, r_{r}
        {}

        int radius() const
        {
            return r_;
        }

        void set_radius(int r) 
        {
            r_ = r;
        }

        void draw() const override
        {
            std::cout << "Drawing circle at " << coord() << " with r: " << r_ << std::endl;
        }
    };
}

#endif // CIRCLE_H
