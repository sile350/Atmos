#pragma once

#include "Renderer/GraphicsContext.h"
#include "Events/Event.h"
#include <GLFW/glfw3.h>

class Window
{
public:
	struct WindowData
	{
		std::string Title;
		uint32_t Width, Height;
		bool VSync;

		std::function<void(Event&)> EventCallback;

		WindowData(const std::string& title = "Atmos", uint32_t width = 1280, uint32_t height = 720)
			: Title(title), Width(width), Height(height) {}
	};

public:
	Window(const WindowData& data);
	~Window();

	void OnUpdate();

	uint32_t GetWidth() const  { return m_Data.Width; }
	uint32_t GetHeight() const { return m_Data.Height; }

	// Window attributes
	void SetEventCallback(const std::function<void(Event&)>& callback) { m_Data.EventCallback = callback; }
	void SetVSync(bool enabled);
	bool IsVSync() const;

	GLFWwindow* GetNativeWindow() const { return m_Window; }

	static std::unique_ptr<Window> Create(const WindowData& data = WindowData());

private:
	void Init(const WindowData& data);
	void Shutdown();
private:
	GLFWwindow* m_Window;
	std::unique_ptr<GraphicsContext> m_Context;

	WindowData m_Data;

};