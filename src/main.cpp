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

const int WIDTH = 600, HEIGHT=600;

int main()
{
    RenderWindow window(VideoMode(WIDTH,HEIGHT), "KPe Fraktals!");

    Fractal fractal;

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
        }
        window.clear();
        window.draw(fractal);
        window.display();
    }
}
