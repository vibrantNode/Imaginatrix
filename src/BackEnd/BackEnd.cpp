#include "BackEnd.h"
#include "API/OpenGL/OGLBackEnd.h"
#include "API/OpenGL/OGLRenderer.h"
#include "API/Vulkan/VkRenderer.h"
#include "API/Vulkan/VkBackEnd.h"
#include "Input/Input.h"
#include "Input/Camera/FPS_Input.h"
#include "Core/Camera.h"
#include <iostream>
#include <string>


#include "GLFW/glfw3.h"

#include "stb_image.h"




namespace BackEnd {

	API _api = API::UNDEFINED;
	GLFWwindow* _window = NULL;
	WindowedMode _windowedMode = WindowedMode::WINDOWED;
	GLFWmonitor* _monitor;
	const GLFWvidmode* _mode;
	bool _forceCloseWindow = false;
	bool _windowHasFocus = true;
	int _windowedWidth = 0;
	int _windowedHeight = 0;
	int _fullscreenWidth = 0;
	int _fullscreenHeight = 0;
	int _currentWindowWidth = 0;
	int _currentWindowHeight = 0;





	// frame
	float lastTime = 0.0f;
	float deltaTime = 0.0f;


	Camera g_camera(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);


	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void window_focus_callback(GLFWwindow* window, int focused);


	// Getters
 
	GLFWwindow* GetWindowPointer() {
		return _window;
	}


	void Init(API api) {
		_api = api;

		if (GetAPI() == API::VULKAN) {
			//VKBackEnd::CreateVulkanInstance();
		}

	

		glfwInit();
		glfwSetErrorCallback([](int error, const char* description) { std::cout << "GLFW Error (" << std::to_string(error) << "): " << description << "\n"; });

		if (GetAPI() == API::OPENGL) {
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
		}
		else if (GetAPI() == API::VULKAN) {
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
			glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_TRUE);
		}
		glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
		glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_TRUE);
		// Resolution and window size
		_monitor = glfwGetPrimaryMonitor();
		_mode = glfwGetVideoMode(_monitor);
		glfwWindowHint(GLFW_RED_BITS, _mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, _mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, _mode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, _mode->refreshRate);


		int width = 1920;
		int height = 1080;

		_fullscreenWidth = _mode->width;
		_fullscreenHeight = _mode->height;
		_windowedWidth = width;
		_windowedHeight = height;

		CreateGLFWWindow(WindowedMode::WINDOWED);
	
		glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);
		glfwSetWindowFocusCallback(_window, window_focus_callback);
		
		SetWindowIcon(_window, "C:/Users/Admin/OneDrive/Desktop/RealTimeRendering/Imaginatrix/res/textures/awesomeface.png");

		if (GetAPI() == API::OPENGL) {
			glfwMakeContextCurrent(_window);
			OGLBackEnd::Init();
			glViewport(0, 0, width, height);
		}
		// Init API specific
		if (GetAPI() == API::OPENGL) {
			
			OGLRenderer::Init();
		}
		else if(GetAPI() == API::VULKAN) {
			//VKBackEnd::Init();
		}
		// Init sub systems
		Input::Init();
		Input::SetGLFWWindow(_window);


		// Set up mouse callback and user pointer
		glfwSetCursorPosCallback(_window, Input::MouseCallback);

		// Disable cursor and set raw mouse motion
		glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		if (glfwRawMouseMotionSupported())
			glfwSetInputMode(_window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

		glfwShowWindow(BackEnd::GetWindowPointer());
		
	}

 

	void BeginFrame() {
		glClear(GL_COLOR_BUFFER_BIT);
		glfwPollEvents();
	
	}



	void EndFrame() {
		// OpenGL
		if (GetAPI() == API::OPENGL) {
			glfwSwapBuffers(_window);
		}
		// Vulkan
		else if (GetAPI() == API::VULKAN) {

		}

	}

	

	void UpdateSubSystems() {
		float currentTime = static_cast<float>(glfwGetTime());
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		// change paramters to either take in a window pointer or whatever it wants to function
		ProcessInput(deltaTime);

		double xpos, ypos;
		glfwGetCursorPos(_window, &xpos, &ypos);
		static double lastX = xpos, lastY = ypos;

		float xoffset = static_cast<float>(xpos - lastX);
		float yoffset = static_cast<float>(lastY - ypos);
		lastX = xpos;
		lastY = ypos;

		g_camera.ProcessMouseMovement(xoffset, yoffset);
		Input::Update(); // Update input states
	}


	void CleanUp() {

		glfwTerminate();
	}



	void CreateGLFWWindow(const WindowedMode& windowedMode) {
		if (windowedMode == WindowedMode::WINDOWED) {
			_currentWindowWidth = _windowedWidth;
			_currentWindowHeight = _windowedHeight;
			_window = glfwCreateWindow(_windowedWidth, _windowedHeight, "Imaginatrix", NULL, NULL);
			glfwSetWindowPos(_window, 0, 0);
		}
		else if (windowedMode == WindowedMode::FULLSCREEN) {
			_currentWindowWidth = _fullscreenWidth;
			_currentWindowHeight = _fullscreenHeight;
			_window = glfwCreateWindow(_fullscreenWidth, _fullscreenHeight, "Imaginatrix", _monitor, NULL);
		}
		_windowedMode = windowedMode;

		// Show the window immediately after creation
		if (_window) {
			glfwShowWindow(_window);
		}
	}

	void SetWindowIcon(GLFWwindow* window, const std::string& iconPath) {
		// Load the image as RGBA
		int width, height, channels;
		unsigned char* data = stbi_load(iconPath.c_str(), &width, &height, &channels, STBI_rgb_alpha);

		if (data) {
			// Create a GLFWimage struct to set the window icon
			GLFWimage icon;
			icon.width = width;
			icon.height = height;
			icon.pixels = data;

			// Set the window icon
			glfwSetWindowIcon(window, 1, &icon);

			// Free the image data after setting the icon
			stbi_image_free(data);
		}
		else {
			std::cerr << "Failed to load window icon.\n";
		}
	}

	void SetWindowedMode(const WindowedMode& windowedMode) {
		if (windowedMode == WindowedMode::WINDOWED) {
			_currentWindowWidth = _windowedWidth;
			_currentWindowHeight = _windowedHeight;
			glfwSetWindowMonitor(_window, nullptr, 0, 0, _windowedWidth, _windowedHeight, _mode->refreshRate);
			glfwSetWindowPos(_window, 0, 0);
		}
		else if (windowedMode == WindowedMode::FULLSCREEN) {
			_currentWindowWidth = _fullscreenWidth;
			_currentWindowHeight = _fullscreenHeight;
			glfwSetWindowMonitor(_window, _monitor, 0, 0, _fullscreenWidth, _fullscreenHeight, _mode->refreshRate);
		}
		_windowedMode = windowedMode;
	}

	void ToggleFullscreen() {
		if (_windowedMode == WindowedMode::WINDOWED) {
			SetWindowedMode(WindowedMode::FULLSCREEN);
		}
		else {
			SetWindowedMode(WindowedMode::WINDOWED);
		}
		if (GetAPI() == API::OPENGL) {
			OGLBackEnd::HandleFrameBufferResized();
		}

	}

	void SetAPI(API api) {
		_api = api;
	}

	const API GetAPI() {
		return _api;
	}



	void SetWindowPointer(GLFWwindow* window) {
		_window = window;
	}
	bool WindowIsOpen() {
		return !(glfwWindowShouldClose(_window) || _forceCloseWindow);
	}
	void ForceCloseWindow() {
		_forceCloseWindow = true;
	}
	bool WindowHasFocus() {
		return _windowHasFocus;
	}
	bool WindowHasNotBeenForceClosed() {
		return !_forceCloseWindow;
	}
	int GetWindowedWidth() {
		return _windowedWidth;
	}

	int GetWindowedHeight() {
		return _windowedHeight;
	}

	int GetFullScreenWidth() {
		return _fullscreenWidth;
	}

	int GetFullScreenHeight() {
		return _fullscreenHeight;
	}

	int GetCurrentWindowWidth() {
		return _currentWindowWidth;
	}

	int GetCurrentWindowHeight() {
		return _currentWindowHeight;
	}

	void ProcessInput(float deltaTime)
	{
		if (Input::IsKeyPressed(GLFW_KEY_W)) {
			g_camera.ProcessKeyboard(CameraMovement::FORWARD, deltaTime);
			
		}
		if (Input::IsKeyPressed(GLFW_KEY_S)) {
			g_camera.ProcessKeyboard(CameraMovement::BACKWARD, deltaTime);
			
		}
		if (Input::IsKeyPressed(GLFW_KEY_A)) {
			g_camera.ProcessKeyboard(CameraMovement::LEFT, deltaTime);
			
		}
		if (Input::IsKeyPressed(GLFW_KEY_D)) {
			g_camera.ProcessKeyboard(CameraMovement::RIGHT, deltaTime);
		}
	}

	Camera& GetCamera()
	{
		return g_camera;
	}
	
	void framebuffer_size_callback(GLFWwindow* /*window*/, int width, int height) {
		if (GetAPI() == API::OPENGL) {
			glViewport(0, 0, width, height);
		}
		else {
			//VulkanBackEnd::MarkFrameBufferAsResized();
		}
	}

	void window_focus_callback(GLFWwindow* /*window*/, int focused) {
		if (focused) {
			BackEnd::_windowHasFocus = true;
		}
		else {
			BackEnd::_windowHasFocus = false;
		}
	}

}