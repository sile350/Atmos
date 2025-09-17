#pragma once

#include "Event.h"

class WindowResizeEvent : public Event
{
public:
	WindowResizeEvent(unsigned int width, unsigned int height)
		: m_Width(width), m_Height(height) {}

	inline unsigned int GetWidth() const { return m_Width; }
	inline unsigned int GetHeight() const { return m_Height; }

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
		return ss.str();
	}

	static EventType GetStaticType() { return EventType::WindowResize; }
	virtual EventType GetEventType() const override { return GetStaticType(); }
	virtual std::string GetName() const override { return "WindowResize"; }

	virtual int GetCategoryFlags() const override { return EventCategoryApplication; }
private:
	unsigned int m_Width, m_Height;
};

class WindowCloseEvent : public Event
{
public:
	WindowCloseEvent() {}

	static EventType GetStaticType() { return EventType::WindowClose; }
	virtual EventType GetEventType() const override { return GetStaticType(); }
	virtual std::string GetName() const override { return "WindowClose"; }

	virtual int GetCategoryFlags() const override { return EventCategoryApplication; }
};

class AppTickEvent : public Event
{
public:
	AppTickEvent() {}

	static EventType GetStaticType() { return EventType::AppTick; }
	virtual EventType GetEventType() const override { return GetStaticType(); }
	virtual std::string GetName() const override { return "AppTick"; }

	virtual int GetCategoryFlags() const override { return EventCategoryApplication; }
};

class  AppUpdateEvent : public Event
{
public:
	AppUpdateEvent() {}

	static EventType GetStaticType() { return EventType::AppUpdate; }
	virtual EventType GetEventType() const override { return GetStaticType(); }
	virtual std::string GetName() const override { return "AppUpdate"; }

	virtual int GetCategoryFlags() const override { return EventCategoryApplication; }
};

class AppRenderEvent : public Event
{
public:
	AppRenderEvent() {}

	static EventType GetStaticType() { return EventType::AppRender; }
	virtual EventType GetEventType() const override { return GetStaticType(); }
	virtual std::string GetName() const override { return "AppRender"; }

	virtual int GetCategoryFlags() const override { return EventCategoryApplication; }
};