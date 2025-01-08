cmake_minimum_required(VERSION "3.13")

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebug$<$<CONFIG:Debug>:Debug>")


add_subdirectory("vendor/glfw" "vendor/glad")


project(Continuum)
set(CMAKE_CXX_STANDARD 17)

# Add GLAD as a library
add_library(glad STATIC vendor/glad/src/glad.c)

# Include directories for GLAD
target_include_directories(glad PUBLIC vendor/glad/include)
find_package(OpenGL REQUIRED)

# Define PROJECT_ROOT_DIR as the absolute path to the project root
set(PROJECT_ROOT_DIR ${CMAKE_SOURCE_DIR})

add_executable(Continuum
#source
	src/main.cpp
	src/Engine.cpp
	
	src/BackEnd/BackEnd.cpp 

	src/Input/Input.cpp

)

target_include_directories(Continuum PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm")
target_include_directories(Continuum PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb")
target_include_directories(Continuum PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")



target_link_libraries(Continuum glfw glad ${CMAKE_DL_LIBS} opengl32)