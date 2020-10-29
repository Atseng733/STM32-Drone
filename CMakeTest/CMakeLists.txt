cmake_minimum_required(VERSION 3.10)
project(CMakeTest)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_CROSSCOMPILING 1)

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)

set(CMAKE_CXX_FLAGS "-mcpu=cortex-m3 -mthumb -ffunction-sections -fdata-sections -Wall -specs=\"nosys.specs\"")

set(CMAKE_EXE_LINKER_FLAGS "-mthumb -mcpu=cortex-m3 -nostartfiles -T ldscripts/stm32f103.ld")

add_executable(${PROJECT_NAME}.elf src/main.cpp)