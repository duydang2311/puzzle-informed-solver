cmake_minimum_required (VERSION 3.10)

project (puzzle-informed-solver LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")

add_executable (${PROJECT_NAME}
	src/main.cpp
)

add_subdirectory(src/direction)

add_subdirectory(src/board)
target_link_libraries(${PROJECT_NAME} PRIVATE board)
