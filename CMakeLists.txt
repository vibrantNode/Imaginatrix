cmake_minimum_required(VERSION "3.13")

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebug$<$<CONFIG:Debug>:Debug>")


add_subdirectory("vendor/glfw" "vendor/glad")

find_package (Vulkan REQUIRED)
project(Continuum)
set(CMAKE_CXX_STANDARD 17)


set(Vulkan_INCLUDE_DIR "C:/VulkanSDK/1.3.296.0/Include")
set(Vulkan_LIBRARY "C:/VulkanSDK/1.3.296.0/Lib/vulkan-1.lib")

include_directories(${Vulkan_INCLUDE_DIR}) 

# Add GLAD as a library
add_library(glad STATIC vendor/glad/src/glad.c)

# Include directories for GLAD
target_include_directories(glad PUBLIC vendor/glad/include)
find_package(OpenGL REQUIRED)

# Define PROJECT_ROOT_DIR as the absolute path to the project root
set(PROJECT_ROOT_DIR ${CMAKE_SOURCE_DIR})

add_executable(Continuum
	
	# Application core
	src/main.cpp
	src/Engine.cpp

	# Back end
	src/BackEnd/BackEnd.cpp 

	# API/OpenGL
	src/API/OpenGL/OGLBackEnd.cpp 
	src/API/OpenGL/OGLRenderer.cpp


	src/API/OpenGL/Types/GL_Shader.cpp
	src/API/OpenGL/Types/GL_Texture.cpp

	#API/Vulkan
	#src/API/Vulkan/VkRenderer.cpp
	#src/API/Vulkan/VkBackEnd.cpp
	
	#src/API/Vulkan/Types/vk_frameData.h
	#src/API/Vulkan/Types/vk_buffer.h
	#src/API/Vulkan/Types/vk_allocation.h 


	# Renderer
	src/Renderer/Renderer.cpp
	src/Renderer/RenderData.cpp 

	src/Renderer/Types/VertexBuffer.cpp 

	# Misc
	src/Utility/ErrorChecking.h 

	# Core
	src/Core/AssetManager.cpp
	src/Core/Camera.cpp
	


	# Input
	src/Input/Input.cpp
	src/Input/Camera/FPS_Input.cpp

	# Game
	src/Game/Game.cpp 
	src/Game/Player.cpp
	src/Game/Scene.cpp

	# Vendor

	vendor/vkbootstrap/VkBootstrap.cpp 


 

)

set_property(TARGET Continuum PROPERTY CXX_STANDARD 20)

target_precompile_headers(Continuum PUBLIC <optional> <vector> <memory> <string> <vector> <unordered_map> <glm/mat4x4.hpp>  <glm/vec4.hpp> <vulkan/vulkan.h>)

target_include_directories(Continuum PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm"
    "${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb"
    "${CMAKE_CURRENT_SOURCE_DIR}/vendor/GLFW"
    "${CMAKE_CURRENT_SOURCE_DIR}/vendor/vkbootstrap"
    "${CMAKE_CURRENT_SOURCE_DIR}/vendor/vma"
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)



target_link_libraries(Continuum
 ${Vulkan_LIBRARY} 
 glfw glad ${CMAKE_DL_LIBS} opengl32)