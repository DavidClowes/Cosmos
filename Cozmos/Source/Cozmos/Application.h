#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace Cozmos

{
	class COZMOS_API Application
	{
	public:
		Application();
		~Application();

		void Run();
	};

	// To be defined in client
	Application* CreateApplication();

}

