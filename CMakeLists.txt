#cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake_minimum_required(VERSION 3.13)

set(CMAKE_TOOLCHAIN_FILE "bbb-toolchain.cmake")

# set the project name and version
project(hello LANGUAGES CXX C VERSION 1.0)
set(TARGET_NAME ${CMAKE_PROJECT_NAME})

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Threads REQUIRED)

add_executable(${TARGET_NAME})
target_sources(${TARGET_NAME} PRIVATE main.cpp)

target_link_libraries(${TARGET_NAME} PRIVATE Threads::Threads)

# Setting up environment variables
export CROSS_COMPILE=${SCRIPT_DIR_ABS}/toolchain/gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-
#export CROSS_COMPILE=arm-linux-gnueabihf-
export CC=${CROSS_COMPILE}gcc
export CPP=${CROSS_COMPILE}cpp
export CXX=${CROSS_COMPILE}g++
export AR=${CROSS_COMPILE}ar
export LD=${CROSS_COMPILE}ld
export RANLIB=${CROSS_COMPILE}ranlib
export STRIP=${CROSS_COMPILE}strip
export NM=${CROSS_COMPILE}nm
export OBJCOPY=${CROSS_COMPILE}objcopy
export SIZE=${CROSS_COMPILE}size
export SYSROOT=$(${CROSS_COMPILE}gcc --print-sysroot)
export ARCH=arm
