#!/bin/bash

TARGET=$1

if [ ! -d "$TARGET" ]; then
    echo "Target directory does not exist."
    exit 1
fi

if [ ! -f "$TARGET/main.cc" ]; then
    echo "main.cc does not exist."
    exit 1
fi

if cpplint --quiet "$TARGET/main.cc"; then
    echo "Linting succeeded."
else
    echo "Linting failed."
    exit 1
fi

if [ -f "$TARGET/a.out" ]; then
    rm "$TARGET/a.out"
fi

if [ -f "$TARGET/Makefile" ]; then
    echo "Compiling with Makefile..."
    make -C "$TARGET"
else
    echo "Compiling with g++..."
    g++ -std=c++20 -o "$TARGET/a.out" -O0 "$TARGET/main.cpp"
fi

if [ -f "$TARGET/a.out" ]; then
    echo "Compilation succeeded."
    echo "Running $TARGET..."
    echo
    "$TARGET/a.out"
else
    echo "Compilation failed."
fi
