cmake_minimum_required(VERSION 3.15)

project(ParallelGaussianMethod VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDART 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
    ${CMAKE_SOURCE_DIR}/SLE
    ${CMAKE_SOURCE_DIR}/interface
    ${CMAKE_SOURCE_DIR}/utils
)

set(HEADERS
    ${CMAKE_SOURCE_DIR}/interface/console_interface.h
    ${CMAKE_SOURCE_DIR}/utils/timer.h
    ${CMAKE_SOURCE_DIR}/SLE/gauss_solver.h
    ${CMAKE_SOURCE_DIR}/SLE/generator_SLE.h
    ${CMAKE_SOURCE_DIR}/SLE/printer_SLE.h
    ${CMAKE_SOURCE_DIR}/SLE/reader_SLE.h
    ${CMAKE_SOURCE_DIR}/SLE/SLE.h
)

set(SOURCES
    ${CMAKE_SOURCE_DIR}/interface/console_interface.cc
    ${CMAKE_SOURCE_DIR}/SLE/gauss_solver.cc
    ${CMAKE_SOURCE_DIR}/SLE/generator_SLE.cc
    ${CMAKE_SOURCE_DIR}/SLE/printer_SLE.cc
    ${CMAKE_SOURCE_DIR}/SLE/reader_SLE.cc
    ${CMAKE_SOURCE_DIR}/SLE/SLE.cc
    ${CMAKE_SOURCE_DIR}/utils/timer.cc
)

add_executable(
    ${PROJECT_NAME}
    ${HEADERS}
    ${SOURCES}
    ${CMAKE_SOURCE_DIR}/main.cc
)

target_compile_options(
    ${PROJECT_NAME}
    PRIVATE
    -Wall
    -Werror
    -Wextra
    -Wpedantic
    -std=c++17
)

# target_link_libraries(${PROJECT_NAME} PRIVATE
#     -fsanitize=address
# )

find_program(CPPCHECK cppcheck)

if(CPPCHECK)
    message(STATUS "cppcheck found: ${CPPCHECK}")
    list(
        APPEND CPPCHECK_ARGS
        "--enable=all"
        "--inconclusive"
        "--quiet"
        "--language=c++"
        "--std=c++17"
    )
    add_custom_target(
        cppcheck
        COMMAND ${CPPCHECK} ${CPPCHECK_ARGS} ${HEADERS} ${SOURCES}
    )
else()
    message(STATUS "cppcheck not found")
endif()

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/.)

include(ClangFormat)

clangformat_setup(
  ${SOURCES}
  ${HEADERS}
)