#include <SFML/Graphics.hpp>
#include <queue>
#include "fractal.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace sf;
using namespace std;

const unsigned int WIDTH = 600;
const unsigned int HEIGHT = 600;

const unsigned int FPS = 60;

sf::Font roboto;
bool fontNotFound = false;

sf::Text getDefText()
{
    sf::Text res;
    res.setFont(roboto);
    res.setScale(0.8,0.8);
    res.setOutlineColor(Color::Black);
    res.setOutlineThickness(3);
    return res;
}

int main()
{
    system("pwd");
    if(!roboto.loadFromFile("./roboto-medium.ttf"))
        fontNotFound = true;

    sf::Text text;
    text.setFont(roboto);
    text.setString("Hello, world!");
    text.setPosition(10,10);

    RenderWindow window(VideoMode(WIDTH,HEIGHT), "KPe Fraktals!");

    Fractal mandelbrot(WIDTH,HEIGHT);

    float mouseX = 0, mouseY = 0;
    float mousePressedX = 0, mousePressedY = 0;
    bool mouseBtnDown = false;

    sf::Clock clock; 
    float maxTime = 0;
    while(window.isOpen())
    {
        clock.restart();

        Event event;
        float mouseWheelScrollDelta = 0;
        while(window.pollEvent(event))
        {
            if(event.type==Event::Closed)
                window.close();
            if(event.type==Event::KeyPressed)
            {
                if(event.key.code==Keyboard::Escape)
                    window.close();
                if(event.key.code==Keyboard::Add)
                    mandelbrot.scale(0.8);
                if(event.key.code==Keyboard::Subtract)
                    mandelbrot.scale(1.2);
                if(event.key.code==Keyboard::Up)
                    mandelbrot.alterPrecision(1.5);
                if(event.key.code==Keyboard::Down)
                    mandelbrot.alterPrecision(0.75);
            }
            if(event.type==Event::MouseButtonPressed)
            {
                mousePressedX = event.mouseButton.x;
                mousePressedY = event.mouseButton.y;
                mouseBtnDown = true;
            }
            if(event.type==Event::MouseButtonReleased)
            {
                mouseBtnDown = false;
                mandelbrot.setSpriteOffset(0,0);
                float mouseDeltaX = mouseX-mousePressedX;
                float mouseDeltaY = mouseY-mousePressedY;
                float coords[2];
                float centerX = WIDTH/2.0-mouseDeltaX;
                float centerY = HEIGHT/2.0-mouseDeltaY;
                mandelbrot.getViewCoords(centerX,centerY,coords);
                mandelbrot.recenterView(coords[0],coords[1]);
            }
            if(event.type==Event::MouseMoved)
            {
                mouseX = event.mouseMove.x;
                mouseY = event.mouseMove.y;
            }
            if(event.type==Event::MouseWheelScrolled)
                mouseWheelScrollDelta += event.mouseWheelScroll.delta;
        }

        // ACCUMULATE MOUSE WHEEL CHANGES
        if(mouseWheelScrollDelta!=0)
                mandelbrot.scale(event.mouseWheelScroll.delta);

        // SET OFFSET FOR MOVING AROUND
        if(mouseBtnDown)
            mandelbrot.setSpriteOffset(mouseX-mousePressedX,mouseY-mousePressedY);

        // DRAW MANDELBROT SPRITE
        window.clear();
        window.draw(mandelbrot);

        // DRAW TEXT
        if(!fontNotFound)
        {
            stringstream ss;
            ss<<fixed<<setprecision(2);

            ss<<mandelbrot.getViewZoom();
            string zoomStr = ss.str();
            sf::Text zoomText = getDefText();
            zoomText.setPosition(10,10);
            zoomText.setString("Zoom: "+ zoomStr+"x");
            window.draw(zoomText);

            ss.str("");
            ss<<maxTime;
            sf::Text timeText = getDefText();
            timeText.setPosition(10,40);
            timeText.setString("Mx time: "+ss.str()+"s");
            window.draw(timeText);

            ss.str("");
            ss<<mandelbrot.getPrecision();
            sf::Text precText = getDefText();
            precText.setPosition(10,70);
            precText.setString("Prec: "+ss.str());
            window.draw(precText);
        }



        window.display();

        // LOCK FPS
        Time elapsedTime = clock.getElapsedTime();
        Time time30FPS = seconds(1.0/FPS);
        if(time30FPS.asSeconds()-elapsedTime.asSeconds()>0)
            sleep(time30FPS-elapsedTime);
        maxTime = max(maxTime, elapsedTime.asSeconds());
    }
}
