#!/bin/bash

# OpenCV with C# Wrapper Build Script
# This script builds OpenCV with shared libraries and C# wrapper support

set -e

# Configuration
BUILD_DIR="build"
INSTALL_DIR="install"
CMAKE_GENERATOR="Ninja"  # Using Ninja for faster builds

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${GREEN}OpenCV with C# Wrapper Build Script${NC}"
echo "=============================================="

# Check if we're in the OpenCV directory
if [ ! -f "CMakeLists.txt" ] || [ ! -d "modules" ]; then
    echo -e "${RED}Error: This script must be run from the OpenCV root directory${NC}"
    exit 1
fi

# Create build directory
echo -e "${YELLOW}Creating build directory...${NC}"
mkdir -p $BUILD_DIR
cd $BUILD_DIR

# Configure CMake
echo -e "${YELLOW}Configuring CMake...${NC}"
cmake -G "$CMAKE_GENERATOR" \
    -DCMAKE_BUILD_TYPE=Debug \
    -DBUILD_SHARED_LIBS=ON \
    -DBUILD_opencv_csharp=ON \
    -DBUILD_opencv_world=ON \
    -DCMAKE_INSTALL_PREFIX="../$INSTALL_DIR" \
    -DWITH_FFMPEG=ON \
    -DWITH_GSTREAMER=ON \
    -DWITH_GTK=ON \
    -DWITH_OPENGL=ON \
    -DWITH_QT=OFF \
    -DBUILD_EXAMPLES=ON \
    -DBUILD_TESTS=ON \
    -DBUILD_PERF_TESTS=ON \
    -DINSTALL_C_EXAMPLES=ON \
    -DINSTALL_PYTHON_EXAMPLES=ON \
    -DOPENCV_EXTRA_MODULES_PATH="" \
    ..

if [ $? -ne 0 ]; then
    echo -e "${RED}CMake configuration failed!${NC}"
    exit 1
fi

echo -e "${GREEN}CMake configuration successful!${NC}"

# Build OpenCV
echo -e "${YELLOW}Building OpenCV...${NC}"
ninja

if [ $? -ne 0 ]; then
    echo -e "${RED}Build failed!${NC}"
    exit 1
fi

echo -e "${GREEN}Build successful!${NC}"

# Install OpenCV
echo -e "${YELLOW}Installing OpenCV...${NC}"
ninja install

if [ $? -ne 0 ]; then
    echo -e "${RED}Installation failed!${NC}"
    exit 1
fi

echo -e "${GREEN}Installation successful!${NC}"

# Check if C# wrapper DLL was created
echo -e "${YELLOW}Checking for C# wrapper DLL...${NC}"
if [ -f "../$INSTALL_DIR/lib/libopencv_csharp_wrapper.so" ] || [ -f "../$INSTALL_DIR/bin/opencv_csharp_wrapper.dll" ]; then
    echo -e "${GREEN}C# wrapper DLL found!${NC}"
    echo "Location: ../$INSTALL_DIR/lib/ (Linux) or ../$INSTALL_DIR/bin/ (Windows)"
else
    echo -e "${YELLOW}Warning: C# wrapper DLL not found. Check build logs.${NC}"
fi

echo -e "${GREEN}OpenCV with C# wrapper build completed successfully!${NC}"
echo "=============================================="
echo "Installation directory: ../$INSTALL_DIR"
echo "C# wrapper DLL: ../$INSTALL_DIR/lib/libopencv_csharp_wrapper.so (Linux) or ../$INSTALL_DIR/bin/opencv_csharp_wrapper.dll (Windows)"
echo ""
echo "To use in C#:"
echo "1. Copy the C# wrapper DLL to your C# project directory"
echo "2. Update your C# code to use the correct DLL name"
echo "3. Make sure all OpenCV dependencies are available"

