#include <SFML/Graphics.hpp>
#include <queue>
#include "fractal.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>

using sf::Color;
using sf::Text;
using sf::Font;
using sf::RenderWindow;
using sf::VideoMode;
using sf::Event;
using sf::Keyboard;

const int WIDTH = 1000, HEIGHT=1000;

int main()
{
    RenderWindow window(VideoMode(WIDTH,HEIGHT), "KPe Fraktals!");

    Fractal fractal(WIDTH,HEIGHT);

    bool dragging = false;
    Event::MouseButtonEvent pressed;
    Event::MouseMoveEvent cursor;
    while(window.isOpen()) {
        Event e;
        while(window.pollEvent(e)) {
            
            if(e.type == Event::Closed)
                window.close();
            if (e.type == Event::Resized)
            {
                sf::FloatRect visibleArea(0, 0, e.size.width, e.size.height);
                window.setView(sf::View(visibleArea));
                fractal.setViewSize(e.size.width, e.size.height);
            }
            if (e.type == Event::MouseButtonPressed)
            {
                dragging = true;
                pressed = e.mouseButton;
            }
            if (e.type == Event::MouseButtonReleased)
            {
                dragging = false;
                auto released = e.mouseButton;
                fractal.setOrigin({(float)-cursor.x+pressed.x, (float)-cursor.y+pressed.y});
                auto origin = fractal.getOrigin();
                float adjustedOriginX = origin.x+window.getSize().x/2;
                float adjustedOriginY = origin.y+window.getSize().y/2;
                float planeCenterX, planeCenterY;
                fractal.getPixelCoords(adjustedOriginX, adjustedOriginY, planeCenterX, planeCenterY);
                fractal.setPlaneCenter(planeCenterX, planeCenterY);
                fractal.setOrigin(0,0);
            }
            if (e.type == Event::MouseMoved)
            {
                cursor = e.mouseMove;
            }
            if (e.type == Event::KeyPressed)
            {
                if( e.key.code == sf::Keyboard::Up) {
                    float zoom = fractal.getZoom();
                    fractal.setZoom(zoom*1.3);
                }
                if(e.key.code == sf::Keyboard::Down) {
                    float zoom = fractal.getZoom();
                    fractal.setZoom(zoom/1.3);
                }
                if(e.key.code == sf::Keyboard::Left) {
                    float precision = fractal.getPrecision();
                    std::cout<<precision<<std::endl;
                    if(precision<0.76) continue;
                    fractal.setPrecision(precision/1.3);
                }
                if(e.key.code == sf::Keyboard::Right) {
                    float precision = fractal.getPrecision();
                    std::cout<<precision<<std::endl;
                    fractal.setPrecision(precision*1.3);
                }
            }
        }
        window.clear();

        if(dragging)
            fractal.setOrigin({(float)-cursor.x+pressed.x, (float)-cursor.y+pressed.y});
        else
            fractal.updateMandelbrot();
        
        window.draw(fractal);
        window.display();
    }
}
