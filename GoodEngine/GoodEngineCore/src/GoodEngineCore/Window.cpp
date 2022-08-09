#include "GoodEngineCore/Window.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "GoodEngineCore/Log.h"
namespace GoodEngine
{
	static bool s_GLFW_initialized = false;
	
	Window::Window(std::string title_, unsigned int width_, unsigned int height_) :m_data({ std::move(title_),width_,height_ })
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
		return m_data.width;
	}
	unsigned int Window::GetHeight()
	{
		return m_data.height;
	}
	void Window::SetEventCallback(const EventCallBackFn& callback)
	{
		m_data.eventCallbackfn = callback;
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
		window = glfwCreateWindow(m_data.width, m_data.height, m_data.title.c_str(), nullptr, nullptr);
		if (!window)
		{
			glfwTerminate();
			LOG_ERROR("Window {0} was not created!!!",m_data.title);
			return -1;
		}

		glfwMakeContextCurrent(window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			LOG_CRITICAL("Failed to initialise GLAD");
			return -1;
		}
		glfwSetWindowUserPointer(window, &m_data);

		glfwSetWindowSizeCallback(window, [](GLFWwindow* pWindow, int width, int height) {
			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(pWindow));
			data.width = width;
			data.height = height;
			EventWindowResize event(width, height);
			data.eventCallbackfn(event);
			});
		glfwSetCursorPosCallback(window, [](GLFWwindow* pWindow, double width, double height) {
			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(pWindow));
			EventMouseMoved event(width, height);
			data.eventCallbackfn(event);
			});
		glfwSetWindowCloseCallback(window, [](GLFWwindow* pWindow) {
			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(pWindow));
			EventWindowClosed event;
			data.eventCallbackfn(event);
			});
		LOG_INFO("Createing window {0} width size {1}x{2}", m_data.title, m_data.width, m_data.height);
		return 0;
	}
	void Window::Shotdown()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}
}