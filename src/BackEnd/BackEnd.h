#pragma once
#include "Common/Common.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <string>


namespace BackEnd {
	
	// Core
	void Init(API api);
	void BeginFrame();
	void UpdateSubSystems();
	void EndFrame();
	void CleanUp();

	// API
	void SetAPI(API api);
	const API GetAPI();

	// Window
	GLFWwindow* GetWindowedPointer();
	void CreateGLFWWindow(const WindowedMode& windowedMode);
	bool WindowIsOpen();
	void SetWindowIcon(GLFWwindow* window, const std::string& iconPath);
	void ToggleFullscreen();
	void SetWindowedMode(const WindowedMode& windowedMode);




}