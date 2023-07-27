#!/bin/bash

# Run tests
cmake -B build && cmake --build build -j && ctest