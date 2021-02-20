cmake_minimum_required(VERSION 3.19)

project(Badger
  VERSION
    1.0
  DESCRIPTION
    "A mean chess engine"
  LANGUAGES
    C
)

FILE(GLOB SOURCE_FILES src/*.c)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(${PROJECT_NAME} ${SOURCE_FILES})