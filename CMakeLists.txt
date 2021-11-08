cmake_minimum_required(VERSION 3.5.1)
project(SimpleJSON)

set(SOURCES             lib/SimpleJSON.hpp
                        lib/SimpleJSON.cpp)

add_library(SimpleJSON STATIC ${SOURCES})
target_include_directories(SimpleJSON PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib)

add_executable(SimpleJSONTest test/main.cpp)
target_link_libraries(SimpleJSONTest PUBLIC SimpleJSON)
target_include_directories(SimpleJSONTest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib)

