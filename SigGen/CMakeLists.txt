cmake_minimum_required(VERSION 3.5)
project(SignalGenerator)

include_directories(include)
file(GLOB_RECURSE SRCS src/*.cpp)
add_executable(SignalGenerator.elf ${SRCS})
add_custom_target(SignalGenerator.hex DEPENDS SignalGenerator.elf COMMAND ${CMAKE_OBJCOPY}\ -Oihex SignalGenerator.elf SignalGenerator.hex)