#include "fractal.hpp"
#include "mandelbrot.h"

#include <iostream>
using namespace std;

sf::Uint8 pixels[3000*3000*4];

const float PLANE_WIDTH = 1.5;

Fractal::Fractal(int width, int height) {
    this->setViewSize(width, height);
    this->setPlaneCenter(-0.5,0);
}

void Fractal::setPlaneCenter(float x, float y) {
    planeCenterX = x, planeCenterY = y;
}

void Fractal::setViewSize(int width, int height) {
    viewWidth = width, viewHeight = height;
}

void Fractal::getPixelCoords(int px, int py, float& x, float& y) const {
    int width = viewWidth, height = viewHeight;
    float planeHeight = height*PLANE_WIDTH/width;
    x = planeCenterX-PLANE_WIDTH+(2*PLANE_WIDTH*px)/(width-1);
    y = planeCenterY-planeHeight+(2*planeHeight*py)/(height-1);
    return;
}

void Fractal::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::Vector2u size = target.getSize();
    int width = size.x;
    int height = size.y;
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            float x, y;
            getPixelCoords(j,i,x,y);
            mandelbrot::color(x,y,&pixels[i*width*4+j*4+0],15);
            pixels[i*width*4+j*4+2]=100;
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
