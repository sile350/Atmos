#pragma once

#include "Core/Window.h"
#include "Events/ApplicationEvent.h"
#include "Events/Event.h"
#include "ImGui/ImGuiLayer.h"

#include "Core/Timestep.h"

class Application
{
public:
	Application(const std::string& name);
	~Application();

	void OnProcessEvent(Event& e);

	Window& GetWindow() { return *m_Window; }

	void Close();

	static Application& Get() { return *s_Instance; }
	std::unique_ptr<ImGuiLayer>& GetImGuiLayer() { return m_ImGuiLayer; }

	void Run();
	bool OnWindowClose(WindowCloseEvent& e);
	bool OnWindowResize(WindowResizeEvent& e);

private:
	void OnUpdate(Timestep ts);
	//void OnImGuiRender();
	void OnEvent(Event& e);
private:
	std::unique_ptr<Window> m_Window;
	std::unique_ptr<ImGuiLayer> m_ImGuiLayer;

	bool m_Running = true;
	bool m_Minimized = false;
	float m_LastFrameTime = 0.0f;
private:
	static Application* s_Instance;
};