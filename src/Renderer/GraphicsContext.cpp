#include "pch.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GL/GL.h>

#include "GraphicsContext.h"

GraphicsContext::GraphicsContext(GLFWwindow* windowHandle)
    : m_WindowHandle(windowHandle)
{
}

void GraphicsContext::Init()
{
    glfwMakeContextCurrent(m_WindowHandle);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

void GraphicsContext::SwapBuffers()
{
    glfwSwapBuffers(m_WindowHandle);
}

std::unique_ptr<GraphicsContext> GraphicsContext::Create(GLFWwindow* window)
{
    return std::make_unique<GraphicsContext>(window);
}
