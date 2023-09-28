#include "Noxpch.h"
#include "WindowsWindow.h"

#include "NOX/EventSystem/ApplicationEvent.h"
#include "NOX/EventSystem/KeyEvent.h"
#include "NOX/EventSystem/MouseEvent.h"

#include <glad/glad.h>

namespace Nox
{
	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int error_code, const char* description) 
	{
		NOX_CORE_ERROR("GLFW Error {0} with description {1}", error_code, description);
	}

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		ShutDown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_WindowData.Title = props.Title;
		m_WindowData.Width = props.Width;
		m_WindowData.Height = props.Height;

		NOX_INFO("Creating Windows window {0} ({1}x{2})", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			NOX_CORE_ASSERT(success, "Could not initialize GLFW!")
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow(props.Width, props.Height, props.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		NOX_CORE_ASSERT(status, "Failed to initialized Glad!");
		glfwSetWindowUserPointer(m_Window, &m_WindowData);
		SetVSync(true);

		//Configuremos los callbacks de GLFW
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height ) 
			{
				//Obtener mas imformacion de glfwGetWindowUserPointer > https://discourse.glfw.org/t/what-is-a-possible-use-of-glfwgetwindowuserpointer/1294
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window); //Casteo para obtener la data como WindowData
				data.Height = height;
				data.Width = width;

				WindowResizeEvent event = WindowResizeEvent(width, height);
				data.EventCallback(event);
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window); 
				
				WindowCloseEvent event = WindowCloseEvent();
				data.EventCallback(event);
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
					case GLFW_PRESS:
					{
						KeyPressedEvent event = KeyPressedEvent(key, 0);
						data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleasedEvent event = KeyReleasedEvent(key);
						data.EventCallback(event);
						break;
					}
					case GLFW_REPEAT:
					{
						KeyPressedEvent event = KeyPressedEvent(key, 1);
						data.EventCallback(event);
						break;
					}
				}

			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				if (action == GLFW_PRESS)
				{
					MouseButtonPressedEvent event = MouseButtonPressedEvent(button);
					data.EventCallback(event);
				}
				else if (action == GLFW_RELEASE) 
				{
					MouseButtonReleasedEvent event = MouseButtonReleasedEvent(button);
					data.EventCallback(event);
				}

			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent event = MouseScrolledEvent(xoffset, yoffset);
				data.EventCallback(event);
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event = MouseMovedEvent((float)xpos, (float)ypos);
				data.EventCallback(event);
			});
	}

	void WindowsWindow::ShutDown()
	{
		NOX_CORE_INFO("Windows Window Shutted down.");
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
		{
			glfwSwapInterval(1);
		}
		else
		{
			glfwSwapInterval(0);
		}
		m_WindowData.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_WindowData.VSync;
	}

}