#include "Rectangle.hpp"

Rectangle::Rectangle() {}

Rectangle::Rectangle(std::string name, float x, float y, float speedX, float speedY, int r, int g, int b, float width, float height)
    :   name(name),
        positionX(x),
        positionY(y),
        baseWidth(width),
        baseHeight(height),
        speedX(speedX),
        speedY(speedY),
        red(r),
        green(g),
        blue(b),
        width(width),
        height(height)
{
}
