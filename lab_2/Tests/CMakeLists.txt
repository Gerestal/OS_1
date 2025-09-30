cmake_minimum_required(VERSION 3.12)
project(ThreadFunctionsTest)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
    add_compile_definitions(_WIN32_WINNT=0x0600)
endif()


add_library(main_functions
    main_functions.cpp
    Header.h
)


target_include_directories(main_functions PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if(WIN32)
    target_link_libraries(main_functions kernel32)
endif()


add_executable(run_tests
    test.cpp
)


target_link_libraries(run_tests main_functions)


target_include_directories(run_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


add_custom_target(test
    COMMAND run_tests
    DEPENDS run_tests
    COMMENT "Running unit tests..."
)

message(STATUS "Project configured successfully!")
message(STATUS "To build: cmake --build .")
message(STATUS "To run tests: cmake --build . --target test OR ./run_tests")
