#!/bin/bash

g++ main.cpp glad.c game.cpp snake.cpp shader.cpp camera.cpp grid.cpp -lm -Wall -lGL -lGLU -lglut -lGLEW -lglfw -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor  -lglfw3



