#include <math.h>
#include "mandelbrot.h"

namespace mandelbrot {
    // returns color of a point in the mandelbrot plane
    void color(float x, float y, uint8 res_rgb[3], int precision=20)
    {
        if(belongs(x,y,precision)){
            res_rgb[0] = 255;
            res_rgb[1] = 255;
            res_rgb[2] = 255;
        } else {
            res_rgb[0] = 0;
            res_rgb[1] = 0;
            res_rgb[2] = 0;
        }
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