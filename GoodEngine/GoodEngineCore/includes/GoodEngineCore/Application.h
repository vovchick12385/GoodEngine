#pragma once
#include <memory>
#include "GoodEngineCore/Event.h"

namespace GoodEngine
{
	class Window;
	class Application
	{
		public:
		Application();
		virtual ~Application();
		Application(const Application&) = delete;
		Application(const Application&&) = delete;
		Application& operator=(Application&) = delete;
		Application&& operator=(Application&&) = delete;

		virtual int start(unsigned int window_width, unsigned int window_height, const char* title);
		virtual void on_update();
	private:
		std::unique_ptr<Window> m_pWindow;
		bool bCloseWindow = false;
		EventDispatcher m_event_dispatcher;
	};
}