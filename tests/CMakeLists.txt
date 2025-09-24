cmake_minimum_required(VERSION 3.15)
project(MyProject LANGUAGES CXX)

if(MSVC)
  set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL" CACHE STRING "" FORCE)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_subdirectory(external/googletest)

add_library(core STATIC
    Project1/main_functions.cpp)
target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Project1)


add_executable(runTests tests/test.cpp)
target_link_libraries(runTests PRIVATE core gtest_main)

enable_testing()
add_test(NAME AllTests COMMAND $<TARGET_FILE:runTests>)

