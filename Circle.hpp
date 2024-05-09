#include <iostream>

#ifndef CIRCLE_HPP
#define CIRCLE_HPP

class Circle
{
public:
    std::string name;
    float       radius;
    int         segments    = 32;
    float       baseRadius;
    float       positionX;
    float       positionY;
    float       speedX;
    float       speedY;
    int         red;
    int         green;
    int         blue;
    float       scale       = 1.0f;
    bool        draw        = true;
    bool        drawText    = true;
    Circle();
    Circle(std::string name, float x, float y, float speedX, float speedY, int r, int g, int b, float radius);
    friend std::ostream &operator << (std::istream &in, const Circle &c);
};
#endif
