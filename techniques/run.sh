#!/bin/bash

TARGET=$1
OPTION=$2

function log() {
    echo -e "\033[1;32m$1\033[0m" >&2
}

function error() {
    echo -e "\033[1;31m$1\033[0m" >&2
}

if [ ! -d "$TARGET" ]; then
    log "Target directory does not exist."
    exit 1
fi

if [ ! -f "$TARGET/main.cpp" ]; then
    log "main.cc does not exist."
    exit 1
fi

if [ -f "$TARGET/*.out" ]; then
    rm "$TARGET/*.out"
fi

if [ -f "$TARGET/Makefile" ]; then
    log "Compiling with Makefile..."
    make -C "$TARGET"
    if [ $? -ne 0 ]; then
        error "Compilation failed."
        exit 1
    fi
else
    log "Compiling with g++..."
    g++ -std=c++20 -o "$TARGET/a.out" -O0 "$TARGET/main.cpp" "$OPTION"
    if [ $? -ne 0 ]; then
        error "Compilation failed."
        exit 1
    fi
fi

if [ -f "$TARGET/a.out" ]; then
    log "Compilation succeeded."
    log "Running $TARGET..."
    log
    "$TARGET/a.out"
else
    log "Compilation failed."
fi
