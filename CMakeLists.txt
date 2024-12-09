cmake_minimum_required(VERSION 3.2)

project(TestContainers)

# Lookup for pre-built gtest
find_package(GTest)

set(CMAKE_INSTALL_PREFIX "C:/GTest_temp")

# Main target
add_executable(
    containers
    DynamicArray/DynamicArray.h 
    LinkedList/LinkedList.h
)

# Test target
add_executable(
    test_containers
    test/test.cpp
)

# Add src to the include directories for the test target
target_include_directories(
    containers PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/DynamicArray"
    "${CMAKE_CURRENT_SOURCE_DIR}/LinkedList"

)
# Add googletest to the include directories for the test target
target_include_directories(
    test_containers PRIVATE
    ${GTEST_INCLUDE_DIRS}
    "${CMAKE_CURRENT_SOURCE_DIR}/test"
)

# Link test target against gtest libraries
target_link_libraries(
    test_containers PRIVATE
    ${GTEST_BOTH_LIBRARIES}
)

set_target_properties(containers PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
set_target_properties(test_containers PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

if (MSVC)
    target_compile_options(
        containers PRIVATE
        /W4
    )
    target_compile_options(
        test_containers PRIVATE
        /W4
    )
else ()
    target_compile_options(
        containers PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(
        test_containers PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()