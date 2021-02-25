cmake_minimum_required(VERSION 3.16)

project(Badger
  VERSION
    1.0
  DESCRIPTION
    "A mean chess engine"
  LANGUAGES
    C
)

set(CMAKE_C_STANDARD 99)


FILE(GLOB SOURCE_FILES src/*.c)

list(REMOVE_ITEM SOURCE_FILES "src/main.c", "src/misc.c")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(${PROJECT_NAME} src/misc.c ${SOURCE_FILES} src/main.c)