cmake_minimum_required(VERSION 3.0)

# Set dependencies
find_library(qcore ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
# Create qcore shared library
add_library(seb-plugin SHARED
	src/GraphSearch.cpp
	src/GridGraph.cpp
)

target_include_directories(seb-plugin PUBLIC include)
target_link_libraries(seb-plugin qcore)
