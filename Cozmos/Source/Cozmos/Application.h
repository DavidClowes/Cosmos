#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"

#include "Cozmos/Events/ApplicationEvent.h"

namespace Cozmos

{
	class COZMOS_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;

		bool m_IsRunning = true;
	};

	// To be defined in client
	Application* CreateApplication();

}

