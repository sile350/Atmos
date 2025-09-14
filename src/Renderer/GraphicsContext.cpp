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
    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

void GraphicsContext::SwapBuffers()
{
    glfwSwapBuffers(m_WindowHandle);
}

std::unique_ptr<GraphicsContext> GraphicsContext::Create(void* window)
{
    return std::make_unique<GraphicsContext>(static_cast<GLFWwindow*>(window));
}
