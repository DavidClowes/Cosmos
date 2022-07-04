#include "Cozmos.h"

#include "imgui/imgui.h"

class ExampleLayer : public Cozmos::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{

	}

	void OnUpdate() override
	{
		if (Cozmos::Input::IsKeyPressed(COZ_KEY_TAB))
		{
			COZ_TRACE("Tab key is pressed!");
		}
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World!");
		ImGui::End();
	}

	void OnEvent(Cozmos::Event& event) override
	{
		// COZ_TRACE("{0}", event);
	}
};

class Sandbox : public Cozmos::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Cozmos::Application* Cozmos::CreateApplication()
{
	return new Sandbox();
}