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
	m_SquareVA = Cozmos::VertexArray::Create();

	float squareVertices[3 * 4] =
	{
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	Cozmos::Ref<Cozmos::VertexBuffer> squareVB;
	squareVB.reset(Cozmos::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
	squareVB->SetLayout({
		{ Cozmos::ShaderDataType::Float3, "a_Position" }
	});
	m_SquareVA->AddVertexBuffer(squareVB);

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	Cozmos::Ref<Cozmos::IndexBuffer> squareIB;
	squareIB.reset(Cozmos::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
	m_SquareVA->SetIndexBuffer(squareIB);

	m_FlatColorShader = Cozmos::Shader::Create("Assets/Shaders/FlatColor.glsl");
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

	Cozmos::Renderer::BeginScene(m_CameraController.GetCamera());
	{
		std::dynamic_pointer_cast<Cozmos::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Cozmos::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);

		Cozmos::Renderer::Submit(m_FlatColorShader, m_SquareVA,
			glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
	}
	Cozmos::Renderer::EndScene();
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
