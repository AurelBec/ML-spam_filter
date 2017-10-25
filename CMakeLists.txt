cmake_minimum_required(VERSION 2.6)

project(ml)
set(EXECUTABLE_NAME "spamFilter")
add_definitions(-std=c++0x)

add_executable(
	${EXECUTABLE_NAME}
	Main.cpp
	Classifier.cpp
	Dico.cpp
)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/" ${CMAKE_MODULE_PATH})
target_link_libraries(${EXECUTABLE_NAME})