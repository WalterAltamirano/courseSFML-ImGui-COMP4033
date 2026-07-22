#!/bin/bash

cmake -B build -S . -GNinja -DCMAKE_EXPORT_COMPILE_COMMANDS=1 
cmake --build build --parallel=$(nproc)