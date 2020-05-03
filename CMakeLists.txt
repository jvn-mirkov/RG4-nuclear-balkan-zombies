cmake_minimum_required(VERSION 3.13)
project(NBZ)

set(CMAKE_CXX_STANDARD 17)




add_executable(nbz  main.cpp Player.cpp Player.h Map.cpp Map.h Box.cpp Box.h ControlMatrix.cpp ControlMatrix.h)
target_link_libraries(nbz -lOpenGL32 -lfreeGLUT -lglu32 )
