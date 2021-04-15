cmake_minimum_required(VERSION 3.17)
project(untitled2)

set(CMAKE_CXX_STANDARD 20)
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "C:/mingw-w64/x86_64-8.1.0-posix-seh-rt_v6-rev0/mingw64/SFML/lib/cmake")
include_directories(headers C:/mingw-w64/x86_64-8.1.0-posix-seh-rt_v6-rev0/mingw64/SFML/include)
find_package(SFML 2.5 COMPONENTS system window graphics)

add_executable(untitled2 main.cpp Game.cpp Game.h)
target_link_libraries(untitled2 sfml-system sfml-window sfml-graphics)