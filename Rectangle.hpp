#include <iostream>

#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

class Rectangle
{
public:
    std::string name;
    float       width;
    float       height;
    float       baseWidth;
    float       baseHeight;
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
    Rectangle();
    Rectangle(std::string name, float x, float y, float speedX, float speedY, int r, int g, int b, float width, float height);
    friend std::istream& operator >> (std::istream& in, Rectangle& r); 
};
#endif
