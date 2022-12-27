#include <math.h>
#include "mandelbrot.h"
#include <iostream>

namespace mandelbrot {
    // returns color of a point in the mandelbrot plane
    void color(float x, float y, uint8 res_rgb[3], int precision=20)
    {
        double z = iterations(x,y,precision)/(float)precision;

        float points[] = {0.0,0.16,0.42,0.6425,1.0};
        uint8 colors[][3] = {  {0,7,100},
                                {32,107,203},
                                {237,255,255},
                                {255,170,0},
                                {0,2,0}};
        for(int i=1;i<5;i++){ // whether z belongs to [points[i-1];points[i]]
            float start = points[i-1];
            float end = points[i];
            if(z<start||z>end) continue;
            float distance = end-start;
            float covered = (z-start)/distance;
            for(int j=0;j<3;j++)
                res_rgb[j] = (colors[i][j]-colors[i-1][j])*covered+colors[i-1][j];
            return;
        }
        std::cout<<z<<std::endl;
        for(int j=0;j<3;j++)
            res_rgb[j] = 255*z;
        return;
    }

    // returns number of iterations where absolute value doesn't seem sus
    int iterations(float x, float y, int limit=20)
    {
        float cx = x, cy = y;
        float zx = 0, zy = 0;
        float zx2 = 0, zy2 = 0;
        for(int i=0;i<limit;i++)
        {
            zy = (2*zx*zy)+cy;
            zx = zx2-zy2+cx;
            zx2 = zx*zx;
            zy2 = zy*zy;
            if((zx2+zy2)>4) return i;
        }
        return limit;
    }

    // returns whether points belongs to the mandelbrot set
    bool belongs(float x, float y, int precision=20)
    {
        float p = sqrt((x-0.25)*(x-0.25)+y*y);
        if(x<=(p-2*p*p+0.25)) return true;
        if((x+1)*(x+1)+y*y<=0.0625) return true;
        return iterations(x,y,precision)==precision;
    }
};