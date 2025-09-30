cmake_minimum_required(VERSION 3.12)
project(ThreadFunctionsTest)

# Настройка стандарта C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Для Windows специфичные настройки
if(WIN32)
    add_compile_definitions(_WIN32_WINNT=0x0600)
endif()

# Создаем библиотеку из основных функций
add_library(main_functions
    main_functions.cpp
    Header.h
)

# Настройки для библиотеки
target_include_directories(main_functions PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if(WIN32)
    target_link_libraries(main_functions kernel32)
endif()

# Создаем исполняемый файл для тестов
add_executable(run_tests
    test.cpp
)

# Линкуем тесты с нашей библиотекой
target_link_libraries(run_tests main_functions)

# Включаем директории для тестов (текущая папка)
target_include_directories(run_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Добавляем удобную цель для запуска тестов
add_custom_target(test
    COMMAND run_tests
    DEPENDS run_tests
    COMMENT "Running unit tests..."
)

message(STATUS "Project configured successfully!")
message(STATUS "To build: cmake --build .")
message(STATUS "To run tests: cmake --build . --target test OR ./run_tests")
