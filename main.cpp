#include <iostream>
#include <memory>
#include <fstream>

#include <SFML/Graphics.hpp>

#include "imgui.h"

#include "imgui-SFML.h"
// int main (){
//     return 0;
// }
int main(int argc, char* argv[]){
    // create a new window of size w*h pixels
    // topleft of the window is (0,0) and bottom-right is (w,h)
    // you will have toread these from the config file

    const int wWidth = 1280;
    const int wHeight = 720;
    sf::RenderWindow window(sf::VideoMode(wWidth, wHeight),"SFML works!");
    window.setFramerateLimit(60);

    // initialize IMGUI and create a clock used for its internal timing
    ImGui::SFML::Init(window);
    sf::Clock deltaClock;

    // scale the imgui ui by a given factor, does not affect text size
    ImGui::GetStyle().ScaleAllSizes(1.0f);

    // the imgui color {r,g,b} wheel requires floats from 0-1 instead of ints from 0-255
    float c[3] = { 0.0f, 1.0f, 1.0f };

    // let's make a shape that we will draw to the screen
    float circleRadius = 50;
    int circleSegments = 32;
    float circleSpeedX = 1.0f;
    float circleSpeedY = 0.5f;
    bool drawCircle = true;
    bool drawText = true;

    // create the sfml circle shape based on our parameters
    sf::CircleShape circle(circleRadius, circleSegments);
    circle.setPosition(10.0f, 10.0f);

    sf::Font myFont;

    if(!myFont.loadFromFile("fonts/enchrome-ascii.ttf")) 
    {
        std::cerr << "could not load font!\n";
        exit(-1);
    }

    // set up the text object that will be drawn to the screen
    sf::Text text("Sample text", myFont, 24);

    // position the top left corner of the text so that the text aligns on the bottom
    // text character size is in pixels, so move the text up from the bottom by its height

    text.setPosition(0, wHeight - (float)text.getCharacterSize());

    // set up a character array to set the text
    char displayString[255] = "Sample Text";

    // main loop - continues for each frame while window is open
    while(window.isOpen())
    {
        // event handling
        sf::Event event;
        while(window.pollEvent(event))
        {
            // pass the event to imgui to be parsed
            ImGui::SFML::ProcessEvent(window, event);

            // this event triggers when the window is closed 
            if (event.type == sf::Event::Closed )
            {
                window.close();
            }

            // this event is triggered when a key is pressed
            if (event.type == sf::Event::KeyPressed)
            {
                // print the key that was pressed to the console
                std::cout << "Key pressed with code = " << event.key.code << "\n";

                // example, what happens when x is pressed
                if( event.key.code == sf::Keyboard::X)
                {
                    // reverse the x direction of the circle on the screen
                    circleSpeedX *= -1.0f;
                }

            }
        }

        // update imgui for this frame with the time that the last frame took
        ImGui::SFML::Update(window, deltaClock.restart());

        // draw the UI
        ImGui::Begin("Window title");
        ImGui::Text("Window text!");
        ImGui::Checkbox("Draw Circle", &drawCircle);
        ImGui::SameLine();
        ImGui::Checkbox("Draw Text", &drawText);
        ImGui::SliderFloat("Radius", &circleRadius, 0.0f, 300.0f);
        ImGui::SliderInt("Sides", &circleSegments, 3, 64);
        ImGui::ColorEdit3("Color Circle", c);
        ImGui::InputText("Text", displayString, 255);
        if(ImGui::Button("Set Text"))
        {
            text.setString(displayString);
        }
        ImGui::SameLine();
        if( ImGui::Button("Reset Circle"))
        {
            circle.setPosition(0, 0);
        }
        ImGui::End();

        // set the circle properties, because they may have been updated with the ui
        circle.setFillColor(sf::Color(c[0]*255, c[1]*255, c[2]*255));
        circle.setPointCount(circleSegments);
        circle.setRadius(circleRadius);

        // basic animation - move each frame if it's still in frame
        circle.setPosition(circle.getPosition().x + circleSpeedX, circle.getPosition().y + circleSpeedY);

        // basic rendering function calls 
        window.clear();
        if( drawCircle )
        {
            window.draw(circle);
        }
        if( drawText )
        {
            window.draw(text);
        }
        ImGui::SFML::Render(window);
        window.display();
    }

    return 0;
}
