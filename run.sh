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

if [ -f "$TARGET/a.out" ]; then
    rm "$TARGET/a.out"
fi

if clang++ -std=c++11 -o "$TARGET/a.out" -O0 "$TARGET/main.cc"; then
    echo "Compilation successful."
    echo "Running $TARGET..."
    echo
    "$TARGET/a.out"
else
    echo "Compilation failed."
fi