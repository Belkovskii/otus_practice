cmake_minimum_required(VERSION 3.2)

project(ProjestWithGTest)

add_executable(
    test_assertions
    test/test.cpp
)

find_package(GTest)

if(GTEST_FOUND)
    message(STATUS "GTest найден: ${GTEST_LIBRARIES}")
else()
    message(FATAL_ERROR "GTest не найден!")
endif()

target_link_libraries(test_assertions 
    GTest::gtest
    GTest::gmock_main
)

if (MSVC)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()
