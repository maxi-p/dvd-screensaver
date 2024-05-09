#include <iostream>
#include <memory>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <SFML/Graphics.hpp>

#include "imgui.h"
#include "imgui-SFML.h"
#include "Circle.hpp"
#include "Rectangle.hpp"

int main(int argc, char* argv[]){
    // create a new window of size w*h pixels
    // topleft of the window is (0,0) and bottom-right is (w,h)
    // you will have toread these from the config file
    std::vector<std::shared_ptr<Circle>> circles;
    std::vector<std::shared_ptr<Rectangle>> rectangles;

    std::string typeText;
    std::string name;
    int         numCirc      {0};
    int         numRect      {0};
    float       radius;
    float       width;
    float       height;
    int         segments    = 32;
    float       positionX;
    float       positionY;
    float       speedX;
    float       speedY;
    int         red;
    int         green;
    int         blue;
    int         wWidth      = 1280;
    int         wHeight     = 720;

    // Extracting configs
    std::ifstream file("ez-config.txt");
    while(file >> typeText){
        if(strcmp(typeText.c_str(), "Window") == 0)
        {
            file >> wWidth >> wHeight;
        }
        if(strcmp(typeText.c_str(), "Circle") == 0)
        {
            file >> name >> positionX >> positionY >> speedX >> speedY >> red >> green >> blue >> radius;
            std::shared_ptr<Circle> p (new Circle(name, positionX, positionY, speedX, speedY, red, green, blue, radius));
            circles.push_back(p);
            numCirc++;
        }
        if(strcmp(typeText.c_str(), "Rectangle") == 0)
        {
            file >> name >> positionX >> positionY >> speedX >> speedY >> red >> green >> blue >> width >> height;
            std::shared_ptr<Rectangle> r (new Rectangle(name, positionX, positionY, speedX, speedY, red, green, blue, width, height));
            rectangles.push_back(r);
            numRect++;
        }
    }

    static int item_current = 0;
    static int item_prev = 0;
    char** items = new char*[numCirc+numRect];
    for(int i=0; i<numCirc; i++)
    {
        items[i] = new char[50];
        // std::cout << circles[i]->name << '\n';
        strcpy(items[i], circles[i]->name.c_str());
        std::cout << items[i] << '\n';
    }
    for(int i=0; i<numRect; i++){
        items[i+numCirc] = new char[50];
        strcpy(items[i+numCirc], rectangles[i]->name.c_str());
        std::cout << items[i+numCirc] << '\n';
    }

    sf::RenderWindow window(sf::VideoMode(wWidth, wHeight),"DVD screensaver!");
    window.setFramerateLimit(60);

    // initialize IMGUI and create a clock used for its internal timing
    ImGui::SFML::Init(window);
    sf::Clock deltaClock;
    ImGui::GetStyle().ScaleAllSizes(1.0f);

    std::vector<sf::CircleShape> sfCircles;
    std::vector<sf::RectangleShape> sfRectangles;
    for(int i = 0; i < circles.size(); i++)
    {
        sf::CircleShape circle(circles[i]->radius, circles[i]->segments);
        circle.setPosition(circles[i]->positionX, circles[i]->positionY);
        circle.setFillColor(sf::Color(circles[i]->red, circles[i]->green, circles[i]->blue));
        sfCircles.push_back(circle);
    }

    for(int i = 0; i < rectangles.size(); i++)
    {
        sf::RectangleShape rectangle(sf::Vector2f(rectangles[i]->width, rectangles[i]->height));
        rectangle.setPosition(rectangles[i]->positionX, rectangles[i]->positionY);
        rectangle.setFillColor(sf::Color(rectangles[i]->red, rectangles[i]->green, rectangles[i]->blue));
        sfRectangles.push_back(rectangle);
    }

    sf::Font myFont;
    if(!myFont.loadFromFile("fonts/enchrome-ascii.ttf")) 
    {
        std::cerr << "could not load font!\n";
        exit(-1);
    }

    // set up a character array to set the text
    char displayString[255];
    strcpy(displayString, circles[item_current]->name.c_str());
    float c[3]              = { (float)circles[item_current]->red/255, (float)circles[item_current]->green/255, (float)circles[item_current]->blue/255 };
    float scale             = 1.0f;
    bool draw               = true;
    static float vec4f[2]   = { abs(circles[item_current]->speedX), abs(circles[item_current]->speedY) };

    // main loop - continues for each frame while window is open
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            // pass the event to imgui to be parsed
            ImGui::SFML::ProcessEvent(window, event);
            if (event.type == sf::Event::Closed )
            {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if( event.key.code == sf::Keyboard::Q)
                {
                    window.close();
                }
            }
        } 

        // update imgui for this frame with the time that the last frame took
        ImGui::SFML::Update(window, deltaClock.restart());
        ImGui::Begin("Shape Properties");
        ImGui::Combo("Shape", &item_current, items, numCirc+numRect);
        ImGui::Checkbox("Draw Shape", &draw);
        ImGui::SliderFloat("Scale", &scale, 1.0f, 10.0f);
        ImGui::SliderFloat2("Velociry", vec4f, 0.001f, 10.0f);
        ImGui::ColorEdit3("Color", c);
        ImGui::InputText("Name", displayString, 255);
        ImGui::End();

        if(item_current < numCirc)
        {
            if(item_current != item_prev)
            {
                draw        = circles[item_current]->draw;
                vec4f[0]    = abs(circles[item_current]->speedX);
                vec4f[1]    = abs(circles[item_current]->speedY);
                c[0]        = (float)circles[item_current]->red/255;
                c[1]        = (float)circles[item_current]->green/255; 
                c[2]        = (float)circles[item_current]->blue/255;
                scale       = circles[item_current]->scale;
                item_prev   = item_current;
            }
            else
            {
                circles[item_current]->draw      = draw;
                circles[item_current]->speedX   /= (abs(circles[item_current]->speedX)/vec4f[0]);
                circles[item_current]->speedY   /= (abs(circles[item_current]->speedY)/vec4f[1]);
                circles[item_current]->radius    = scale*circles[item_current]->baseRadius;
                circles[item_current]->red       = (int)(c[0]*255);
                circles[item_current]->green     = (int)(c[1]*255);
                circles[item_current]->blue      = (int)(c[2]*255);
                circles[item_current]->scale     = scale;
            }
        }
        else
        {
            if(item_current != item_prev)
            {
                draw        = rectangles[item_current-numCirc]->draw;
                vec4f[0]    = abs(rectangles[item_current-numCirc]->speedX);
                vec4f[1]    = abs(rectangles[item_current-numCirc]->speedY);
                c[0]        = (float)rectangles[item_current-numCirc]->red/255;
                c[1]        = (float)rectangles[item_current-numCirc]->green/255; 
                c[2]        = (float)rectangles[item_current-numCirc]->blue/255;
                scale       = rectangles[item_current-numCirc]->scale;
                item_prev   = item_current;
            }
            else
            {
                rectangles[item_current-numCirc]->draw       = draw;
                rectangles[item_current-numCirc]->speedX    /= (abs(rectangles[item_current-numCirc]->speedX)/vec4f[0]);
                rectangles[item_current-numCirc]->speedY    /= (abs(rectangles[item_current-numCirc]->speedY)/vec4f[1]);
                rectangles[item_current-numCirc]->width      = scale*rectangles[item_current-numCirc]->baseWidth;
                rectangles[item_current-numCirc]->height     = scale*rectangles[item_current-numCirc]->baseHeight;
                rectangles[item_current-numCirc]->red        = (int)(c[0]*255);
                rectangles[item_current-numCirc]->green      = (int)(c[1]*255);
                rectangles[item_current-numCirc]->blue       = (int)(c[2]*255);
                rectangles[item_current-numCirc]->scale      = scale;
            }
        }

        // Bouncing from walls logic: circles
        for(int i = 0; i < circles.size(); i++)
        {
            auto cur = sfCircles[i].getPosition();
            if(cur.x + circles[i]->radius*2 >= wWidth || cur.x < 0)
            {
                circles[i]->speedX *= -1.0f;
            }
            if(cur.y + circles[i]->radius*2 >= wHeight || cur.y < 0)
            {
                circles[i]->speedY *= -1.0f;
            }
        }

        // Bouncing from walls logic: rectangles
        for(int i = 0; i < rectangles.size(); i++)
        {
            auto cur = sfRectangles[i].getPosition();
            if(cur.x + rectangles[i]->width >= wWidth || cur.x < 0)
            {
                rectangles[i]->speedX *= -1.0f;
            }
            if(cur.y + rectangles[i]->height >= wHeight || cur.y < 0)
            {
                rectangles[i]->speedY *= -1.0f;
            }
        }

        // Movement
        for(int i = 0; i < sfCircles.size(); i++)
        {
            auto cur = sfCircles[i].getPosition();
            circles[i]->positionX = cur.x + circles[i]->speedX;
            circles[i]->positionY = cur.y + circles[i]->speedY;
        }
        for(int i = 0; i < sfRectangles.size(); i++)
        {
            auto cur = sfRectangles[i].getPosition();
            rectangles[i]->positionX = cur.x + rectangles[i]->speedX;
            rectangles[i]->positionY = cur.y + rectangles[i]->speedY;
        }

        // SFML
        for(int i = 0; i < sfCircles.size(); i++)
        {
            sfCircles[i].setPosition(circles[i]->positionX, circles[i]->positionY);
            sfCircles[i].setFillColor(sf::Color(circles[i]->red, circles[i]->green, circles[i]->blue));
            sfCircles[i].setScale(circles[i]->scale, circles[i]->scale);
        }
        for(int i = 0; i < sfRectangles.size(); i++)
        {
            sfRectangles[i].setPosition(rectangles[i]->positionX, rectangles[i]->positionY);
            sfRectangles[i].setFillColor(sf::Color(rectangles[i]->red, rectangles[i]->green, rectangles[i]->blue));
            sfRectangles[i].setScale(rectangles[i]->scale, rectangles[i]->scale);
        }

        // Rendering
        window.clear();
        for(int i = 0; i < sfCircles.size(); i++)
        {
            if(circles[i]->draw)
            {
                window.draw(sfCircles[i]);
            }
        }
        for(int i = 0; i < sfRectangles.size(); i++)
        {
            if(rectangles[i]->draw)
            {
                window.draw(sfRectangles[i]);
            }
        }
        ImGui::SFML::Render(window);
        window.display();
    }

    // Deallocating
    for(int i=0; i<numCirc+numRect; i++)
    {
        delete[] items[i];
    }
    delete[] items;

    ImGui::SFML::Shutdown();
    return 0;
}
