#pragma once
#include "IMCommon/Common.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <string>
#include <Input/Input.h>
#include <memory>	
#include "Core/Camera.h"


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
	GLFWwindow* GetWindowPointer();
	void CreateGLFWWindow(const WindowedMode& windowedMode);
	bool WindowIsOpen();
	void SetWindowIcon(GLFWwindow* window, const std::string& iconPath);
	void ToggleFullscreen();
	void SetWindowedMode(const WindowedMode& windowedMode);
	void ForceCloseWindow();
	bool WindowHasFocus();
	bool WindowHasNotBeenForceClosed();
	int GetWindowedWidth();

	int GetWindowedHeight();

	int GetFullScreenWidth();

	int GetFullScreenHeight();

	int GetCurrentWindowWidth();

	int GetCurrentWindowHeight();





}