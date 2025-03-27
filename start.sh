#!/bin/bash

echo "Starting script..."
g++ main.cpp Post.cpp SocialMedia.cpp User.cpp -o main
./main.exe
echo "Script completed successfully."