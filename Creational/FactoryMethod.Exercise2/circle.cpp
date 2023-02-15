#include "circle.hpp"
#include "shape_factories.hpp"

using namespace std;
using namespace Drawing;

static bool is_registered = SingletonShapeFactory::instance().register_creator(Circle::id, &std::make_unique<Circle>);
