#pragma once
#include "GoodEngineCore/Event.h"
#include <string>
#include <functional>

struct GLFWwindow;

namespace GoodEngine
{
	class Window
	{
	public:
		using EventCallBackFn = std::function<void(BaseEvent&)>;
		Window(std::string title_, unsigned int width_, unsigned int height_);
		~Window();
		Window(const Window&) = delete;
		Window(const Window&&) = delete;
		Window& operator=(Window&) = delete;
		Window&& operator=(Window&&) = delete;

		int start(unsigned int window_width, unsigned int window_height, const char* title);
		void on_update();
		unsigned int GetWidth();
		unsigned int GetHeight();
		void SetEventCallback(const EventCallBackFn& callback);
	private:
		struct WindowData
		{
			std::string title;
			unsigned int width, height;
			EventCallBackFn eventCallbackfn;
		};
		int Init();
		void Shotdown();
		GLFWwindow* window;
		WindowData m_data;
		
	};
}