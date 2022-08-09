#include "GoodEngineCore/Window.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "GoodEngineCore/Log.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_opengl3.h"

namespace GoodEngine
{
	static bool s_GLFW_initialized = false;
	
	GLfloat point[] = {
		0.0f, 0.5f,0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f
	};

	GLfloat colors[] = {
		1.0f, 0.0f,1.0f,
		0.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f
	};

	const char* vertex_shader =
		"#version 460\n"
		"layout(location =0) in vec3 vertex_position;"
		"layout(location = 1) in vec3 vertex_color;"
		"out vec3 color;"
		"void main(){"
		"	color = vertex_color;"
		" gl_Position = vec4(vertex_position,1.0);"
		"}";

	const char* fragment_shader =
		"#version 460\n"
		"in vec3 color;"
		"out vec4 frag_color;"
		"void main(){"
		"frag_color = vec4(color,1.0);"
		"}";

	GLuint shader_program;
	GLuint vao;

	Window::Window(std::string title_, unsigned int width_, unsigned int height_) :m_data({ std::move(title_),width_,height_ })
	{
		Init();
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui_ImplOpenGL3_Init();
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

		glClearColor(0, 0, 0, 0);
		/*render here*/
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader_program);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES,0,3);

		/*Widgets render here */
		/*ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize.x = static_cast<float>(GetWidth());
		io.DisplaySize.y = static_cast<float>(GetHeight());
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();
		ImGui::ShowDemoWindow();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());*/
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

		glfwSetFramebufferSizeCallback(window, [](GLFWwindow* pWindow, int width, int height) {
			glViewport(0, 0, width, height);
			});

		GLuint vs = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vs, 1, &vertex_shader, nullptr);
		glCompileShader(vs);
		GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fs, 1, &fragment_shader, nullptr);
		glCompileShader(fs);

		shader_program = glCreateProgram();
		glAttachShader(shader_program, vs);
		glAttachShader(shader_program, fs);
		glLinkProgram(shader_program);

		glDeleteShader(vs);
		glDeleteShader(fs);

		GLuint points_VBO = 0;
		glGenBuffers(1, &points_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, points_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);

		GLuint colors_VBO = 0;
		glGenBuffers(1, &colors_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, colors_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colors),colors, GL_STATIC_DRAW);

		glGenVertexArrays(1,&vao);
		glBindVertexArray(vao);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, points_VBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colors_VBO);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		return 0;
	}
	void Window::Shotdown()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}
}