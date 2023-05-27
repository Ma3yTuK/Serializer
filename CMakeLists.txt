cmake_minimum_required(VERSION 3.14)

project(Serializer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(Serializer SHARED
    src/Serializer/Types/BaseType.cpp
    src/Serializer/Types/Array.cpp
    src/Serializer/Types/Boolean.cpp
    src/Serializer/Types/Null.cpp
    src/Serializer/Types/Numeric.cpp
    src/Serializer/Types/Object.cpp
    src/Serializer/Types/String.cpp
)

target_include_directories(Serializer
    PRIVATE include
)
