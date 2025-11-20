#!/bin/bash

# Create build directory if it doesn't exist
mkdir -p build
cd build

# Run CMake
cmake ..

# Build the project
make -j$(nproc)

# Check if build was successful
if [ $? -eq 0 ]; then
    echo "Build successful!"
    
    # Run the application
    ./qt_chat_client
else
    echo "Build failed!"
    exit 1
fi
