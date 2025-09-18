#pragma once

#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "Events/ApplicationEvent.h"

class ImGuiLayer
{
public:
	ImGuiLayer();
	~ImGuiLayer();

    void Init();
    void Shutdown();

	void OnEvent(Event& e);

	void Begin();
	void End();

	void Render();

	void BlockEvents(bool block) { m_BlockEvents = block; }
private:
	bool m_BlockEvents = true;
	float m_Time = 0.0f;
};