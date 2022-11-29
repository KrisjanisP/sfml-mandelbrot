#include "fractal.hpp"
#include <iostream>
#include <complex>
#include <thread>
#include <cmath>

Fractal::Fractal(uint width,uint height):WIDTH(width),HEIGHT(height)
{
    this->pixels.resize(WIDTH*HEIGHT*4,0);
    this->texture.create(WIDTH,HEIGHT);
    this->precomputeColors();
    this->regenerate();
}

void Fractal::regenerate()
{
    const int threads = 20;
    std::thread threadArr[threads];
    uint threadWidth = WIDTH/threads;
    uint tl[threads][2],br[threads][2];
    for(int i=0;i<threads;i++)
    {
        tl[i][0] = threadWidth*i;
        tl[i][1] = 0;
        br[i][0] = threadWidth*(i+1)-1;
        br[i][1] = HEIGHT-1;
        threadArr[i]=std::thread(&Fractal::generate,this,tl[i],br[i]);
    }
    for(int i=0;i<threads;i++)
        threadArr[i].join();
    this->texture.update(pixels.data());
    this->sprite.setTexture(texture,true);
}

void Fractal::scale(int levels)
{
    this->viewZoom *= pow(1.3,levels);
    this->viewWidth = this->viewMaxWidth/this->viewZoom;
    this->viewHeight = this->viewMaxHeight/this->viewZoom;
    regenerate();
}

void Fractal::setSpriteOffset(int screenX, int screenY)
{
    sprite.setPosition(screenX, screenY);
}

float Fractal::getViewZoom()
{
    return this->viewZoom;
}

void Fractal::getViewCoords(int screenX, int screenY, float res[2])
{
    float xFrac = (float)2*viewWidth/(float)WIDTH;
    float yFrac = (float)2*viewHeight/(float)HEIGHT;
    res[0] = viewX-viewWidth+xFrac*screenX;
    res[1] = viewY-viewHeight+yFrac*screenY;
}

void Fractal::recenterView(float x, float y)
{
    viewX = x;
    viewY = y;
    regenerate();
}

void Fractal::precomputeColors()
{
    float ultraFractalPos[5] = {0.0,0.16,0.42,0.6425,1};
    sf::Uint8 ultraFractalRGB[5][3] = {{0,7,100},{32,107,203},{237,255,255},{255,170,0},{0,2,0}};
    for(int i=0;i<5;i++) ultraFractalPos[i]*=COLORS;
    for(int pos=0;pos<COLORS;pos++)
    {
        for(int i=1;i<5;i++)
        {
            if(pos<=ultraFractalPos[i])
            {
                sf::Uint8* aRGB = ultraFractalRGB[i-1];
                sf::Uint8* bRGB = ultraFractalRGB[i];
                this->colors[pos][0] = aRGB[0]+(bRGB[0]-aRGB[0])*((pos-ultraFractalPos[i-1])/(ultraFractalPos[i]-ultraFractalPos[i-1]));
                this->colors[pos][1] = aRGB[1]+(bRGB[1]-aRGB[1])*((pos-ultraFractalPos[i-1])/(ultraFractalPos[i]-ultraFractalPos[i-1]));
                this->colors[pos][2] = aRGB[2]+(bRGB[2]-aRGB[2])*((pos-ultraFractalPos[i-1])/(ultraFractalPos[i]-ultraFractalPos[i-1]));
                break;
            }
        }
    }
}

void Fractal::getColors(int iters, sf::Uint8 rgb[3], float x, float y)
{
    int i = (iters*(COLORS-1))/precision;
    rgb[0] = this->colors[i][0];
    rgb[1] = this->colors[i][1];
    rgb[2] = this->colors[i][2];
}

void Fractal::generate(uint tl[2], uint br[2])
{
    float xFrac = (float)2*viewWidth/(float)WIDTH;
    float yFrac = (float)2*viewHeight/(float)HEIGHT;

    for(uint y=tl[1];y<=br[1];y++)
    {
        for(uint x=tl[0];x<=br[0];x++)
        {
            float ax = viewX-viewWidth+xFrac*x;
            float ay = viewY-viewHeight+yFrac*y;
            int iters = iterations(ax,ay);
            sf::Uint8 rgb[3];
            getColors(iters,rgb,ax,ay);
            pixels[(y*WIDTH+x)*4+0]=rgb[0];
            pixels[(y*WIDTH+x)*4+1]=rgb[1];
            pixels[(y*WIDTH+x)*4+2]=rgb[2];
            pixels[(y*WIDTH+x)*4+3]=255;
        }
    }
}

int Fractal::getPrecision()
{
    return this->precision;
}

void Fractal::draw(sf::RenderTarget& target,
                   const sf::RenderStates states) const
{
    target.draw(sprite,states);
}

void Fractal::alterPrecision(float multiplier)
{
    precision *= multiplier;
    precision = std::max(precision, 2);
    regenerate();
}

