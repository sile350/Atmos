#include "pch.h"
#include "Window.h"

#include "Input.h"

#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"
#include "Events/KeyEvent.h"

#include "Renderer/GraphicsContext.h"
#include "Core/Log.h"

static uint8_t s_GLFWWindowCount = 0;

static void GLFWErrorCallback(int error, const char* description)
{
	Log::CoreError("GLFW Error ({0}): {1}", error, description);
}

Window::Window(const WindowData& data)
{
	Init(data);
}

Window::~Window()
{
	Shutdown();
}

std::unique_ptr<Window> Window::Create(const WindowData& data)
{
	return std::make_unique<Window>(data);
}

void Window::Init(const WindowData& data)
{
	m_Data.Title = data.Title;
	m_Data.Width = data.Width;
	m_Data.Height = data.Height;

	Log::CoreInfo("Creating window {0} ({1}, {2})", data.Title, data.Width, data.Height);

	if (s_GLFWWindowCount == 0)
	{
		glfwInit();
		glfwSetErrorCallback(GLFWErrorCallback);
	}

	m_Window = glfwCreateWindow((int)data.Width, (int)data.Height, m_Data.Title.c_str(), nullptr, nullptr);
	++s_GLFWWindowCount;

	m_Context = GraphicsContext::Create(m_Window);
	m_Context->Init();

	glfwSetWindowUserPointer(m_Window, &m_Data);
	SetVSync(true);

	// Set GLFW callbacks
	glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
	{
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		data.Width = width;
		data.Height = height;

		WindowResizeEvent event(width, height);
		data.EventCallback(event);
	});

	glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
	{
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		WindowCloseEvent event;
		data.EventCallback(event);
	});

	glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		switch (action)
		{
		case GLFW_PRESS:
		{
			KeyPressedEvent event(key, 0);
			data.EventCallback(event);
			break;
		}
		case GLFW_RELEASE:
		{
			KeyReleasedEvent event(key);
			data.EventCallback(event);
			break;
		}
		case GLFW_REPEAT:
		{
			KeyPressedEvent event(key, 1);
			data.EventCallback(event);
			break;
		}
		}
	});

	glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
	{
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		KeyTypedEvent event(keycode);
		data.EventCallback(event);
	});

	glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
	{
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		switch (action)
		{
		case GLFW_PRESS:
		{
			MouseButtonPressedEvent event(button);
			data.EventCallback(event);
			break;
		}
		case GLFW_RELEASE:
		{
			MouseButtonReleasedEvent event(button);
			data.EventCallback(event);
			break;
		}
		}
	});

	glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
	{
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		MouseScrolledEvent event((float)xOffset, (float)yOffset);
		data.EventCallback(event);
	});

	glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
	{
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		MouseMovedEvent event((float)xPos, (float)yPos);
		data.EventCallback(event);
	});
}

void Window::Shutdown()
{
	glfwDestroyWindow(m_Window);
	--s_GLFWWindowCount;

	if (s_GLFWWindowCount == 0)
	{
		glfwTerminate();
	}
}

void Window::OnUpdate()
{
	m_Context->SwapBuffers();
	glfwPollEvents();
}

void Window::SetVSync(bool enabled)
{
	if (enabled) glfwSwapInterval(1);
	else glfwSwapInterval(0);

	m_Data.VSync = enabled;
}

bool Window::IsVSync() const
{
	return m_Data.VSync;
}
