#include "cozpch.h"
#include "Application.h"

#include "Cozmos/Events/ApplicationEvent.h"
#include "Cozmos/Log.h"

#include <GLFW/glfw3.h>

namespace Cozmos
{
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (m_IsRunning)
		{
			glClearColor(0, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			glfwWaitEvents();
			m_Window->OnUpdate();
		}
	}

}