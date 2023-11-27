cmake_minimum_required(VERSION 3.22)
project(checksums)

# Find the OpenSSL package
find_package(OpenSSL REQUIRED)

# Include the OpenSSL headers
include_directories(${OPENSSL_INCLUDE_DIR})


set(CMAKE_CXX_STANDARD 17)

add_executable(
        checksums
        main.cpp
        Hasher.h
        Hasher.cpp
)

# Link OpenSSL to executable
target_link_libraries(checksums OpenSSL::SSL OpenSSL::Crypto)