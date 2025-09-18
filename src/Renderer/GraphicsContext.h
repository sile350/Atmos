#pragma once

#include "Core/Log.h"
#include <GLFW/glfw3.h>

class GraphicsContext
{
public:
	GraphicsContext(GLFWwindow* windowHandle);
	~GraphicsContext() = default;

	void Init();
	void SwapBuffers();

	static std::unique_ptr<GraphicsContext> Create(GLFWwindow* window);
private:
	GLFWwindow* m_WindowHandle;
};

