#!/bin/bash

echo "Starting script..."
g++ main.cpp Player.cpp Board.cpp Gameengine.cpp -std=c++14 -o main
./main.exe
echo "Script completed successfully."