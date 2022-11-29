#pragma once

// returns number of iterations where absolute value doesn't seem sus
int mandelbrot_iterations(float x, float y, int limit=20);

// returns whether points belongs to the mandelbrot set
bool mandelbrot_belongs(float x, float y, int precision=20);