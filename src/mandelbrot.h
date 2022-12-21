#pragma once

typedef unsigned char uint8;

namespace mandelbrot {
    // returns color of a point in the mandelbrot plane
    void color(float x, float y, uint8 res_rgb[3], int precision);
    // returns number of iterations where absolute value doesn't seem sus
    int iterations(float x, float y, int limit);
    // returns whether points belongs to the mandelbrot set
    bool belongs(float x, float y, int precision);
};