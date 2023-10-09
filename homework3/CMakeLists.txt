cmake_minimum_required(VERSION 3.12)
project(CustomContainers)

add_executable(CustomContainers
    main.cpp
    LinkedList/LinkedList.h
    DynamicArray/DynamicArray.h
)

target_include_directories(CustomContainers  ${CMAKE_CURRENT_SOURCE_DIR}/release)


set_target_properties(CustomContainers PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

find_package(GTest CONFIG REQUIRED)
target_link_libraries(CustomContainers
    PRIVATE GTest::gtest GTest::gtest_main
)


