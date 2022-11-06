#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(16.0f / 9.0f)
{
}

void Sandbox2D::OnAttach()
{
	
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Cozmos::Timestep ts)
{
	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	Cozmos::RenderCommand::SetClearColor({ 0.1, 0.1, 0.1, 1 });
	Cozmos::RenderCommand::Clear();

	Cozmos::Renderer2D::BeginScene(m_CameraController.GetCamera());
	{
		Cozmos::Renderer2D::DrawQuad({ 0.0f, 0.0f, }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	}
	Cozmos::Renderer2D::EndScene();
	// std::dynamic_pointer_cast<Cozmos::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);
	// std::dynamic_pointer_cast<Cozmos::OpenGLShader>(m_FlatColorShader)->Bind();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();

}

void Sandbox2D::OnEvent(Cozmos::Event& e)
{
	m_CameraController.OnEvent(e);
}
