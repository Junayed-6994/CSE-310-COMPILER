#!/bin/bash

# stop if error

set -e

echo "Compiling..."

g++ -std=c++17 -Wall -fsanitize=address -g 2205132_main.cpp -o 2205132_symboltable

if [ $? -eq 0 ]; then
echo "Build successful: ./2205132_symboltable"
else
echo "Build failed"
exit 1
fi
