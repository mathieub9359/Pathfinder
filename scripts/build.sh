#!/bin/bash

BUILD_DIR="../build"

if [ ! -d "$BUILD_DIR" ]; then
    echo "Creating build directory"
    mkdir "$BUILD_DIR"
fi

cd "$BUILD_DIR"

echo "Running cmake..."
cmake ..

echo "Running make..."
make

echo "Build process completed"