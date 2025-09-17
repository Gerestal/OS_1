add_library(Reporter STATIC
    Reporter.cpp
)

target_include_directories(Reporter
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
