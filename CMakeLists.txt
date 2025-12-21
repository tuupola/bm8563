cmake_minimum_required(VERSION 3.10)
project(bm8563 VERSION 0.5.0 LANGUAGES C)

if (ESP_PLATFORM)

    idf_component_register(
        SRCS "bm8563.c"
        INCLUDE_DIRS "."
    )

else()

    add_library(bm8563 bm8563.c)
    target_include_directories(bm8563 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

endif()