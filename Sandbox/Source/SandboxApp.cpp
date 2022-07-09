#include "Cozmos.h"

#include "imgui/imgui.h"

class ExampleLayer : public Cozmos::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(Cozmos::VertexArray::Create());

		float vertices[3 * 7] =
		{
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<Cozmos::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Cozmos::VertexBuffer::Create(vertices, sizeof(vertices)));
		Cozmos::BufferLayout layout =
		{
			{ Cozmos::ShaderDataType::Float3, "a_Position" },
			{ Cozmos::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Cozmos::IndexBuffer> indexBuffer;
		indexBuffer.reset(Cozmos::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		// Square //

		m_SquareVA.reset(Cozmos::VertexArray::Create());

		float squareVertices[3 * 4] =
		{
		   -0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		std::shared_ptr<Cozmos::VertexBuffer> squareVB;
		squareVB.reset(Cozmos::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Cozmos::ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Cozmos::IndexBuffer> squareIB;
		squareIB.reset(Cozmos::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
		
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;

			uniform mat4 u_ViewProjection;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
		
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(new Cozmos::Shader(vertexSrc, fragmentSrc));

		std::string blueShadervertexSrc = R"(
			#version 330 core
		
			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;

			uniform mat4 u_ViewProjection;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string blueShaderfragmentSrc = R"(
			#version 330 core
		
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_BlueShader.reset(new Cozmos::Shader(blueShadervertexSrc, blueShaderfragmentSrc));
	}

	void OnUpdate(Cozmos::Timestep timestep) override
	{
		if (Cozmos::Input::IsKeyPressed(COZ_KEY_LEFT))
			m_CameraPosition.x -= m_CameraSpeed * timestep;

		if (Cozmos::Input::IsKeyPressed(COZ_KEY_RIGHT))
			m_CameraPosition.x += m_CameraSpeed * timestep;

		if (Cozmos::Input::IsKeyPressed(COZ_KEY_DOWN))
			m_CameraPosition.y -= m_CameraSpeed * timestep;

		if (Cozmos::Input::IsKeyPressed(COZ_KEY_UP))
			m_CameraPosition.y += m_CameraSpeed * timestep;

		if (Cozmos::Input::IsKeyPressed(COZ_KEY_A))
			m_CameraRotation -= m_CameraRotationSpeed * timestep;

		if (Cozmos::Input::IsKeyPressed(COZ_KEY_D))
			m_CameraRotation += m_CameraRotationSpeed * timestep;

		Cozmos::RenderCommand::SetClearColor({ 0.1, 0.1, 0.1, 1 });
		Cozmos::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Cozmos::Renderer::BeginScene(m_Camera);
		{
			Cozmos::Renderer::Submit(m_BlueShader, m_SquareVA);
			Cozmos::Renderer::Submit(m_Shader, m_VertexArray);
		}
		Cozmos::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
	}

	void OnEvent(Cozmos::Event& event) override
	{
	}

private:

	std::shared_ptr<Cozmos::Shader> m_Shader;
	std::shared_ptr<Cozmos::VertexArray> m_VertexArray;

	std::shared_ptr<Cozmos::Shader> m_BlueShader;
	std::shared_ptr<Cozmos::VertexArray> m_SquareVA;

	Cozmos::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraSpeed = 0.1f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 2.0f;
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