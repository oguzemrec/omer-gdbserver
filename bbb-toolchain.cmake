set(SYSROOT_PATH "/home/oemre/workspace/buildroot-bbb/buildroot/output/host/arm-buildroot-linux-gnueabihf/sysroot")
set(CROSS_COMPILE "/home/oemre/workspace/buildroot-bbb/buildroot/output/host/bin/arm-buildroot-linux-gnueabihf")

message(STATUS "Using sysroot path: ${SYSROOT_PATH}")

set(CROSS_COMPILE_CC "${CROSS_COMPILE}-gcc")
set(CROSS_COMPILE_CXX "${CROSS_COMPILE}-g++")
set(CROSS_COMPILE_LD "${CROSS_COMPILE}-ld")
set(CROSS_COMPILE_AR "${CROSS_COMPILE}-ar")
set(CROSS_COMPILE_RANLIB "${CROSS_COMPILE}-ranlib")
set(CROSS_COMPILE_STRIP "${CROSS_COMPILE}-strip")
set(CROSS_COMPILE_NM "${CROSS_COMPILE}-nm")
set(CROSS_COMPILE_OBJCOPY "${CROSS_COMPILE}-objcopy")
set(CROSS_COMPILE_SIZE "${CROSS_COMPILE}-size")

# At the very least, cross compile gcc and g++ have to be set!
find_program (CROSS_COMPILE_CC_FOUND ${CROSS_COMPILE_CC} REQUIRED)
find_program (CROSS_COMPILE_CXX_FOUND ${CROSS_COMPILE_CXX} REQUIRED)

set(CMAKE_CROSSCOMPILING TRUE)
set(CMAKE_SYSROOT "${SYSROOT_PATH}")

# Define name of the target system
set(CMAKE_SYSTEM_NAME "Linux")
set(CMAKE_SYSTEM_PROCESSOR "arm")

# Define the compiler
set(CMAKE_C_COMPILER ${CROSS_COMPILE_CC})
set(CMAKE_CXX_COMPILER ${CROSS_COMPILE_CXX})

set(CMAKE_PREFIX_PATH 
	"${CMAKE_PREFIX_PATH}"
	"${SYSROOT_PATH}/usr/lib/${CROSS_COMPILE}"
)

set(CMAKE_C_FLAGS 
	"-march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=hard ${COMMON_FLAGS}" 
	CACHE STRING "Flags for Beagle Bone Black"
)
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS}" 
	CACHE STRING "Flags for Beagle Bone Black"
)

set(CMAKE_FIND_ROOT_PATH 
	"${CMAKE_INSTALL_PREFIX};${CMAKE_PREFIX_PATH};${CMAKE_SYSROOT}"
)

# search for programs in the build host directories
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)