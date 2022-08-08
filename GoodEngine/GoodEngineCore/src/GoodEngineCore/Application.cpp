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
		while (true)
		{
			m_pWindow->on_update();
			on_update();
		}
	}

	void Application::on_update()
	{
	}
}

