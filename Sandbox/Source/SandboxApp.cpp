#include "Cozmos.h"

class Sandbox : public Cozmos::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Cozmos::Application* Cozmos::CreateApplication()
{
	return new Sandbox();
}