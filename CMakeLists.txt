project(HotSwap C CXX)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/macros")

include(CheckCXXCompilerFlag)
include(CheckCXXSourceRuns)
include(CheckIncludeFiles)

include(CheckPlatform)

# OpenSSL
set(OPENSSL_EXPECTED_VERSION 1.0.0)
find_package(OpenSSL REQUIRED)

# Boost
include(ConfigureBoost)

add_subdirectory(src)
add_subdirectory(example)
