#include "GoodEngineCore/Application.h"
#include "GoodEngineCore/Log.h"
#include "GoodEngineCore/Window.h"
namespace GoodEngine
{
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	int Application::start(unsigned int window_width, unsigned int window_height, const char* title)
	{
		m_pWindow = std::make_unique<Window>(title, window_width, window_height);
		
		m_event_dispatcher.add_event_listener<EventMouseMoved>([](EventMouseMoved& event)
			{
				LOG_INFO("[MouseMoved] Mouse moved to {0}x{1}", event.x, event.y);
			});
		
		m_event_dispatcher.add_event_listener<EventWindowResize>([](EventWindowResize& event)
			{
				LOG_INFO("[EVENT] Changed size to {0}x{1}", event.x, event.y);
			});

		m_event_dispatcher.add_event_listener<EventWindowClosed>([&](EventWindowClosed& event)
			{
				LOG_INFO("[WindowClose]");
				bCloseWindow = true;
			});
		
		m_pWindow->SetEventCallback([&](BaseEvent& event) {
			m_event_dispatcher.dispatch(event);
			});
		while (!bCloseWindow)
		{
			m_pWindow->on_update();
			on_update();
		}
		m_pWindow = nullptr;
		return 0;
	}

	void Application::on_update()
	{
	}
}

