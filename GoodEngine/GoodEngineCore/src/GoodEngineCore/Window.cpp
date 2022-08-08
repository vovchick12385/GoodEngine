#include "GoodEngineCore/Window.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "GoodEngineCore/Log.h"
namespace GoodEngine
{
	static bool s_GLFW_initialized = false;
	
	Window::Window(std::string title_, unsigned int width_, unsigned int height_):title(title_),width(width_),height(height_)
	{
		Init();
	}
	Window::~Window()
	{
		Shotdown();
	}
	int Window::start(unsigned int window_width, unsigned int window_height, const char* title)
	{
		return 0;
	}
	void Window::on_update()
	{
		glClearColor(1, 0, 0, 0);
		/*render here*/
		glClear(GL_COLOR_BUFFER_BIT);
		/*swap buffers here*/
		glfwSwapBuffers(window);
		glfwPollEvents();

	}
	unsigned int Window::GetWidth()
	{
		return width;
	}
	unsigned int Window::GetHeight()
	{
		return height;
	}
	int Window::Init()
	{
		if (!s_GLFW_initialized)
		{
			if (!glfwInit())
			{
				LOG_CRITICAL("Can't initialized GLFW!!!");
				return -1;
			}
			s_GLFW_initialized = true;
		}
		window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
		if (!window)
		{
			glfwTerminate();
			LOG_ERROR("Window {0} was not created!!!",title);
			return -1;
		}

		glfwMakeContextCurrent(window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			LOG_CRITICAL("Failed to initialise GLAD");
			return -1;
		}
		
		LOG_INFO("Createing window {0} width size {1}x{2}", title, width, height);
		return 0;
	}
	void Window::Shotdown()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}
}