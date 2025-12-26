# Basic system configuration
set(CMAKE_SYSTEM_NAME Darwin)  # Darwin is the core of macOS/iOS
set(CMAKE_SYSTEM_PROCESSOR arm64)  # Target ARM64 architecture
set(CMAKE_OSX_ARCHITECTURES arm64)  # Build only for arm64 (no x86_64)
set(CMAKE_OSX_DEPLOYMENT_TARGET 12.0)  # Minimum iOS version support

# Compiler configuration
set(CMAKE_C_COMPILER "/usr/bin/clang")  # Path to Apple's clang for C
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")  # Path to Apple's clang++ for C++

# SDK configuration
set(CMAKE_OSX_SYSROOT iphoneos)  # Use iOS SDK (automatically found by Xcode)

# Cross-compilation search behavior
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)  # Don't search for programs in sysroot
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)  # Only search for libraries in sysroot
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)  # Only search for includes in sysroot
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)  # Only search for packages in sysroot

# Compiler flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -arch arm64 -fembed-bitcode -isysroot ${CMAKE_OSX_SYSROOT}")
# -arch arm64: Target ARM64 architecture
# -fembed-bitcode: Include bitcode for App Store submission
# -isysroot: Specify iOS SDK path

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -arch arm64 -fembed-bitcode -isysroot ${CMAKE_OSX_SYSROOT}")
# Same flags for C++ compilation

# Mark as iOS build
set(IOS TRUE)  # Can be used in CMakeLists.txt for iOS-specific logic
