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

const int WIDTH = 600, HEIGHT=600, FPS=60;

int main()
{
    Font roboto;
    if(!roboto.loadFromFile("./roboto-medium.ttf"))
        return 1;

    RenderWindow window(VideoMode(WIDTH,HEIGHT), "KPe Fraktals!");
}
