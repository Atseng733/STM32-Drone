cmake_minimum_required(VERSION 3.5)
project(test_project)

include_directories(include)
include_directories($ENV{IDF_PATH}/components/freertos/include/freertos)
include_directories($ENV{IDF_PATH}/components/freertos/include/freertos/private)
include_directories($ENV{IDF_PATH}/components/freertos/port/esp8266/include/freertos/)

#LINK_DIRECTORIES($ENV{IDF_PATH}/components/freertos/freertos)

file(GLOB SOURCES "src/*.cpp")

add_executable(test_project ${SOURCES})
#TARGET_LINK_LIBRARIES(test_project )