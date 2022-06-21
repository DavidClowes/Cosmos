#pragma once

#ifdef COZ_PLATFORM_WINDOWS

extern Cozmos::Application* Cozmos::CreateApplication();

int main(int argc, char** argv)
{
	Cozmos::Log::Init();

	auto app = Cozmos::CreateApplication();
	app->Run();
	delete app;
}

#endif