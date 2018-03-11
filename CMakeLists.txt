project(extract_giga_word_pair)
cmake_minimum_required(VERSION 2.7 FATAL_ERROR)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

if (CMAKE_BULLD_TYPE MATCHES Debug)
	set( CMAKE_CXX_FLAGS "-w -msse3 -funroll-loops -std=c++11 -00" )
else()
	set( CMAKE_CXX_FLAGS "-w -msse3 -funroll-loops -std=c++11 -Ofast -march=native" )
	endif()
	
	add_subdirectory(src)