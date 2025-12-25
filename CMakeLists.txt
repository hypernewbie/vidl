cmake_minimum_required(VERSION 3.10)
project(VidlProject)

find_package(Python3 REQUIRED COMPONENTS Interpreter)

set(VIDL_INPUT "${CMAKE_CURRENT_SOURCE_DIR}/tests/test.cpp")
set(VIDL_OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/vidl_generated.h")

add_custom_command(
    OUTPUT ${VIDL_OUTPUT}
    COMMAND ${Python3_EXECUTABLE} "${CMAKE_CURRENT_SOURCE_DIR}/vidl.py" ${VIDL_INPUT} ${VIDL_OUTPUT}
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/vidl.py" ${VIDL_INPUT}
    COMMENT "Generating ${VIDL_OUTPUT} from ${VIDL_INPUT}"
)

add_executable(MyGame main.cpp ${VIDL_OUTPUT})
target_include_directories(MyGame PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

add_executable(VidlTest tests/test.cpp ${VIDL_OUTPUT})
target_include_directories(VidlTest PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
