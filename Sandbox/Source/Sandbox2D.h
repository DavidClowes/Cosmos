#pragma once

#include "Cozmos.h"

class Sandbox2D : public Cozmos::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Cozmos::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Cozmos::Event& e) override;
	
private:
	Cozmos::OrthographicCameraController m_CameraController;

	// Temp
	Cozmos::Ref<Cozmos::VertexArray> m_SquareVA;
	Cozmos::Ref<Cozmos::Shader> m_FlatColorShader;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};

