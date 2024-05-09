#include "Circle.hpp"

Circle::Circle() {}

Circle::Circle(std::string name, float x, float y, float speedX, float speedY, int r, int g, int b, float radius)
    :   name(name),
        baseRadius(radius),
        positionX(x),
        positionY(y),
        speedX(speedX),
        speedY(speedY),
        red(r),
        green(g),
        blue(b),
        radius(radius)

{
}

std::ostream& operator << (std::ostream& cout, const Circle& circle){
    cout << "Name: " << circle.name << " X: " << circle.positionX << " Y: " << circle.positionY << " speedX: " << circle.speedX << " speedY: " << circle.speedY << " red: " << circle.red << " green: " << circle.green << " blue: " << circle.blue << " radius: " << circle.radius;
    return cout;
}
