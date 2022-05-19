mkdir -p ./bin
g++  ./src/main.cpp ./src/fractal.cpp -o ./bin/mandelbrot -lsfml-graphics -lsfml-window -lsfml-system
cp ./assets/roboto-medium.ttf ./bin/roboto-medium.ttf
