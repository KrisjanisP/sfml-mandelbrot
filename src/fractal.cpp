#include "fractal.hpp"
#include "mandelbrot.h"

#include <iostream>
using namespace std;

sf::Uint8 pixels[3000*3000*4];

const float PLANE_WIDTH = 2;
const float P_CENTER_X = -0.5;
const float P_CENTER_Y = 0;

void Fractal::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::Vector2u size = target.getSize();
    int width = size.x;
    int height = size.y;
    float planeHeight = height*PLANE_WIDTH/width;
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            float x, y;
            x = P_CENTER_X-PLANE_WIDTH+(2*PLANE_WIDTH*j)/(width-1);
            y = P_CENTER_Y-planeHeight+(2*planeHeight*i)/(height-1);
            mandelbrot::color(x,y,&pixels[i*width*4+j*4+0],15);
            pixels[i*width*4+j*4+3]=255;
        }
    }
    sf::Image image;
    image.create(width,height,pixels);
    sf::Texture texture;
    texture.loadFromImage(image);
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(this->getPosition());
    sprite.setOrigin(this->getOrigin());
    target.draw(sprite);
}