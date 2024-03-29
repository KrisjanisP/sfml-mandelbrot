SRC_DIR=./src
BIN_DIR=./bin

$(BIN_DIR)/exec: $(BIN_DIR)/fractal.o $(BIN_DIR)/main.o $(BIN_DIR)/mandelbrot.o
	mkdir -p $(BIN_DIR)
	g++ $^ -o $@ -lsfml-graphics -lsfml-window -lsfml-system

$(BIN_DIR)/fractal.o: $(SRC_DIR)/fractal.cpp $(SRC_DIR)/fractal.hpp
	mkdir -p $(BIN_DIR)
	g++ -c $(SRC_DIR)/fractal.cpp -o $@

$(BIN_DIR)/main.o: $(SRC_DIR)/main.cpp
	mkdir -p $(BIN_DIR)
	g++ -c $(SRC_DIR)/main.cpp -o $@

$(BIN_DIR)/mandelbrot.o: $(SRC_DIR)/mandelbrot.cpp $(SRC_DIR)/mandelbrot.h
	mkdir -p $(BIN_DIR)
	g++ -c $(SRC_DIR)/mandelbrot.cpp -o $@

run: $(BIN_DIR)/exec
	$(BIN_DIR)/exec
