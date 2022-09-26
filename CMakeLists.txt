cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(ECO)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse4.2 -mavx -mavx2")

file(GLOB_RECURSE SOURCE "src/*.cpp")

add_executable(ECO ${SOURCE})
include_directories("${PROJECT_SOURCE_DIR}")

add_subdirectory(dependencies)

target_link_libraries(ECO PRIVATE
	dependency_imgui
	dependency_glfw
	dependency_OpenGL
	dependency_GLEW
	dependency_DataContainer)

set(CONTAINER_PATH ${PROJECT_SOURCE_DIR}/test)

add_custom_command(
  OUTPUT ${CONTAINER_PATH}.hpp
  COMMAND GENERATOR ${CONTAINER_PATH}.txt
  DEPENDS ${CONTAINER_PATH}.txt
  VERBATIM)

add_custom_target(GENERATE_CONTAINER DEPENDS ${CONTAINER_PATH}.hpp)

add_dependencies(ECO GENERATE_CONTAINER)