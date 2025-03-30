#!/bin/bash

echo "Starting script..."
g++ main.cpp Poll.cpp System.cpp User.cpp -o main
./main.exe
echo "Script completed successfully."