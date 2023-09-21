cmake_minimum_required(VERSION 3.12)
project(CustomContainers)

add_executable(CustomContainers
    main.cpp
    LinkedList/LinkedList.h
    DynamicArray/DynamicArray.h
)

set_target_properties(CustomContainers PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)