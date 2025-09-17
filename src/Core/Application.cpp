#include "pch.h"

#include "Core/Application.h"
#include "Core/Log.h"
#include "Renderer/Renderer.h"
#include "Core/Input.h"

Application* Application::s_Instance = nullptr;

Application::Application(const std::string& name)
{
	s_Instance = this;
	m_Window = Window::Create(Window::WindowData(name));
	m_Window->SetEventCallback(std::bind(&Application::OnProcessEvent, this, std::placeholders::_1));

	Renderer::Init();
}

Application::~Application()
{
	Renderer::Shutdown();
}

void Application::Close()
{
	m_Running = false;
}

void Application::OnProcessEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
	dispatcher.Dispatch<WindowResizeEvent>(std::bind(&Application::OnWindowResize, this, std::placeholders::_1));

	OnEvent(e);
}

void Application::Run()
{
	while (m_Running)
	{
		float time = (float)glfwGetTime();
		Timestep timestep = time - m_LastFrameTime;
		m_LastFrameTime = time;

		if (!m_Minimized)
		{

			OnUpdate(timestep);

			/*m_ImGuiLayer->Begin();
			{
				SL_PROFILE_SCOPE("LayerStack OnImGuiRender");

				for (Layer* layer : m_LayerStack)
					layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();*/
		}

		m_Window->OnUpdate();
	}
}

bool Application::OnWindowClose(WindowCloseEvent& e)
{
	m_Running = false;
	return true;
}

bool Application::OnWindowResize(WindowResizeEvent& e)
{
	if (e.GetWidth() == 0 || e.GetHeight() == 0)
	{
		m_Minimized = true;
		return false;
	}

	m_Minimized = false;
	Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

	return false;
}

void Application::OnUpdate(Timestep ts)
{
	Renderer::SetClearColor({ 1.0f, 0.1f, 0.1f, 1.0f });
	Renderer::Clear();
}

void Application::OnEvent(Event& e)
{
}
