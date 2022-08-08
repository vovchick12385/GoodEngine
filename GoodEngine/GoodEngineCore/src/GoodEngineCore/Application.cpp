#include "GoodEngineCore/Application.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "GoodEngineCore/Log.h"


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
		GLFWwindow* window;
		if (!glfwInit())
		{
			LOG_ERROR("OpenGL was not init!!!");
			return -1;
		}
		window = glfwCreateWindow(window_width, window_height, title, NULL, NULL);
		if (!window)
		{
			glfwTerminate();
			LOG_ERROR("Window was not created!!!");
			return -1;
		}
		glfwMakeContextCurrent(window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			LOG_CRITICAL("Failde to initialise OpenGL");
			return -1;
		}

		glClearColor(1, 0, 0, 0);

		while (!glfwWindowShouldClose(window))
		{
			/*render here*/
			glClear(GL_COLOR_BUFFER_BIT);
			/*swap buffers here*/
			glfwSwapBuffers(window);
			glfwPollEvents();
			on_update();
		}
		glfwTerminate();
		return 0;
	}

	void Application::on_update()
	{
	}
}

