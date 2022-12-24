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

const int WIDTH = 600, HEIGHT=700;

int main()
{
    RenderWindow window(VideoMode(WIDTH,HEIGHT), "KPe Fraktals!");

    Fractal fractal;

    bool dragging = false;
    Event::MouseButtonEvent pressed;
    Event::MouseButtonEvent released;
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
            }
            if (e.type == Event::MouseButtonPressed)
            {
                dragging = true;
                pressed = e.mouseButton;
            }
            if (e.type == Event::MouseButtonReleased)
            {
                dragging = false;
                released = e.mouseButton;
            }
            if (e.type == Event::MouseMoved)
            {
                cursor = e.mouseMove;
            }
        }
        std::cout<<dragging<<std::endl;
        window.clear();
        window.draw(fractal);
        if(dragging) {
            fractal.setOrigin({(float)cursor.x, (float)cursor.y});
        }
        window.display();
    }
}
