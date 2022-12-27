#include "fractal.hpp"
#include "mandelbrot.h"

#include <iostream>
using namespace std;

sf::Uint8 pixels[3000*3000*4];

Fractal::Fractal(int width, int height) {
    planeWidth = 1.5;
    precision = 15;
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
    float planeHeight = height*planeWidth/width;
    x = planeCenterX-planeWidth+(2*planeWidth*px)/(width-1);
    y = planeCenterY-planeHeight+(2*planeHeight*py)/(height-1);
    return;
}

float Fractal::getZoom() const {
    return 1.5/planeWidth;
}

void Fractal::setZoom(float zoom) {
    planeWidth=1.5/zoom;
}

float Fractal::getPrecision() const {
    return precision/15;
}

void Fractal::setPrecision(float _precision) {
    precision = _precision*15;
}


void Fractal::updateMandelbrot() {
    for(int i=0;i<viewHeight;i++){
        for(int j=0;j<viewWidth;j++){
            float x, y;
            getPixelCoords(j,i,x,y);
            mandelbrot::color(x,y,&pixels[i*viewWidth*4+j*4+0],precision);
            pixels[i*viewWidth*4+j*4+2]=100;
            pixels[i*viewWidth*4+j*4+3]=255;
        }
    }
}

void Fractal::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::Image image;
    image.create(viewWidth,viewHeight,pixels);
    sf::Texture texture;
    texture.loadFromImage(image);
    sf::Sprite sprite;
    sprite.setTexture(texture);

    sprite.setPosition(this->getPosition());
    sprite.setOrigin(this->getOrigin());

    target.draw(sprite);
}
