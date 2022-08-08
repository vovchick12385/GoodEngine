#pragma once

namespace GoodEngine
{

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
	};
}