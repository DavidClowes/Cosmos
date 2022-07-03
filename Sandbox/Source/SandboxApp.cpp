#include "Cozmos.h"

class ExampleLayer : public Cozmos::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{

	}

	void OnUpdate() override
	{
		COZ_INFO("ExampleLayer::Update");
	}

	void OnEvent(Cozmos::Event& event) override
	{
		COZ_TRACE("{0}", event);
	}
};

class Sandbox : public Cozmos::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Cozmos::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Cozmos::Application* Cozmos::CreateApplication()
{
	return new Sandbox();
}