add_library(Creator STATIC
    Creator.cpp
)

target_include_directories(Creator
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
