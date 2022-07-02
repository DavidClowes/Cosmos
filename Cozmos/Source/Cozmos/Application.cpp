#include "cozpch.h"
#include "Application.h"

#include "Cozmos/Events/ApplicationEvent.h"
#include "Cozmos/Log.h"

namespace Cozmos
{
	Application::Application()
	{

	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		COZ_TRACE(e);

		while (true);
	}

}