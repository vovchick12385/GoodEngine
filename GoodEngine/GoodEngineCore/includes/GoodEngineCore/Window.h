#pragma once
#include <string>


struct GLFWwindow;

namespace GoodEngine
{
	class Window
	{
	public:
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
	private:
		int Init();
		void Shotdown();
		GLFWwindow* window;
		unsigned int width, height;
		std::string title;
	};
}